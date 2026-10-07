"""Parser for Fly-in map files.

Reads a map file describing zones, connections and drone count, and
builds a MapData object. Raises ParsingError with line information on
any invalid input.
"""

from dataclasses import dataclass, field
from pathlib import Path
from typing import Union

VALID_ZONE_TYPES = frozenset({"normal", "blocked", "restricted", "priority"})
ZONE_METADATA_KEYS = frozenset({"zone", "color", "max_drones"})
CONNECTION_METADATA_KEYS = frozenset({"max_link_capacity"})


class ParsingError(Exception):
    """Raised when the map file contains a syntax or semantic error."""


@dataclass
class Zone:
    """A zone (node) of the drone network with its static attributes."""

    name: str
    x: int
    y: int
    zone_type: str = "normal"
    color: str = "none"
    max_drones: int = 1
    is_start: bool = False
    is_end: bool = False

    @property
    def entry_cost(self) -> int:
        """Return the movement cost (in turns) of entering this zone."""
        if self.zone_type == "restricted":
            return 2
        return 1


@dataclass
class Connection:
    """A bidirectional edge between two zones."""

    zone1: str
    zone2: str
    max_link_capacity: int = 1

    def links(self, zone_name: str) -> bool:
        """Return True if this connection touches the given zone."""
        return zone_name in (self.zone1, self.zone2)


@dataclass
class MapData:
    """Everything parsed from a map file (static, never changes)."""

    nb_drones: int
    zones: dict[str, Zone] = field(default_factory=dict)
    connections: list[Connection] = field(default_factory=list)

    def neighbors(self, zone_name: str) -> list[str]:
        """Return the names of all zones connected to the given zone."""
        result: list[str] = []
        for conn in self.connections:
            if conn.zone1 == zone_name:
                result.append(conn.zone2)
            elif conn.zone2 == zone_name:
                result.append(conn.zone1)
        return result

    @property
    def start_zone(self) -> Zone:
        """Return the unique start zone."""
        for zone in self.zones.values():
            if zone.is_start:
                return zone
        raise ParsingError("No start_hub defined in map.")

    @property
    def end_zone(self) -> Zone:
        """Return the unique end zone."""
        for zone in self.zones.values():
            if zone.is_end:
                return zone
        raise ParsingError("No end_hub defined in map.")


def _parse_positive_int(value: str, key: str, line_num: int) -> int:
    """Parse a metadata value as a strictly positive integer."""
    try:
        number = int(value)
    except ValueError as exc:
        raise ParsingError(
            f"Line {line_num}: '{key}' must be an integer, got '{value}'."
        ) from exc
    if number <= 0:
        raise ParsingError(
            f"Line {line_num}: '{key}' must be a positive integer, got {number}."
        )
    return number


def _parse_metadata(
    content: str, allowed_keys: frozenset[str], line_num: int
) -> dict[str, str]:
    """Parse 'key=value' pairs found inside a [ ... ] block."""
    metadata: dict[str, str] = {}
    for token in content.split():
        if "=" not in token:
            raise ParsingError(
                f"Line {line_num}: invalid metadata '{token}', "
                "expected key=value."
            )
        key, _, value = token.partition("=")
        if not key or not value:
            raise ParsingError(
                f"Line {line_num}: invalid metadata '{token}', "
                "expected key=value."
            )
        if key not in allowed_keys:
            raise ParsingError(
                f"Line {line_num}: unknown metadata key '{key}'."
            )
        metadata[key] = value
    return metadata


def _extract_brackets(
    tokens: list[str], line_num: int
) -> tuple[list[str], str]:
    """Split tokens into plain tokens and bracketed metadata content.

    Expects tokens to end with a single [ ... ] block. Returns the
    tokens without the block plus the block content without brackets.
    Raises ParsingError on malformed brackets.
    """
    bracket_start = None
    for index, token in enumerate(tokens):
        if "[" in token:
            bracket_start = index
            break
    if bracket_start is None:
        return tokens, ""
    block = " ".join(tokens[bracket_start:])
    if not block.startswith("[") or not block.endswith("]"):
        raise ParsingError(
            f"Line {line_num}: malformed metadata block '{block}'."
        )
    return tokens[:bracket_start], block[1:-1]


def _validate_zone_name(name: str, line_num: int) -> None:
    """Ensure a zone name contains no dashes or spaces."""
    if "-" in name:
        raise ParsingError(
            f"Line {line_num}: zone name '{name}' must not contain dashes."
        )


def _parse_zone_line(
    tokens: list[str], line_num: int, is_start: bool, is_end: bool
) -> Zone:
    """Build a Zone from the tokens of a hub definition line."""
    plain, meta_content = _extract_brackets(tokens, line_num)
    if len(plain) != 4:
        raise ParsingError(
            f"Line {line_num}: expected '<type>: <name> <x> <y> [metadata]', "
            f"got {len(plain)} fields."
        )
    _, name, x_str, y_str = plain
    _validate_zone_name(name, line_num)
    try:
        x = int(x_str)
        y = int(y_str)
    except ValueError as exc:
        raise ParsingError(
            f"Line {line_num}: coordinates must be integers, "
            f"got '{x_str} {y_str}'."
        ) from exc

    metadata = _parse_metadata(meta_content, ZONE_METADATA_KEYS, line_num)

    zone_type = metadata.get("zone", "normal")
    if zone_type not in VALID_ZONE_TYPES:
        raise ParsingError(
            f"Line {line_num}: invalid zone type '{zone_type}', "
            f"expected one of {sorted(VALID_ZONE_TYPES)}."
        )

    max_drones = 1
    if "max_drones" in metadata:
        max_drones = _parse_positive_int(
            metadata["max_drones"], "max_drones", line_num
        )
    if is_start or is_end:
        max_drones = len(metadata) and max_drones or 1

    color = metadata.get("color", "none")

    return Zone(
        name=name,
        x=x,
        y=y,
        zone_type=zone_type,
        color=color,
        max_drones=max_drones,
        is_start=is_start,
        is_end=is_end,
    )


def _parse_connection_line(
    tokens: list[str], line_num: int, zones: dict[str, Zone]
) -> Connection:
    """Build a Connection from the tokens of a connection line."""
    plain, meta_content = _extract_brackets(tokens, line_num)
    if len(plain) != 2:
        raise ParsingError(
            f"Line {line_num}: expected 'connection: <zone1>-<zone2> "
            f"[metadata]', got {len(plain)} fields."
        )
    endpoints = plain[1].split("-")
    if len(endpoints) != 2 or not all(endpoints):
        raise ParsingError(
            f"Line {line_num}: invalid connection '{plain[1]}', "
            "expected '<zone1>-<zone2>'."
        )
    zone1, zone2 = endpoints
    for name in (zone1, zone2):
        if name not in zones:
            raise ParsingError(
                f"Line {line_num}: connection references undefined "
                f"zone '{name}'."
            )

    metadata = _parse_metadata(
        meta_content, CONNECTION_METADATA_KEYS, line_num
    )
    capacity = 1
    if "max_link_capacity" in metadata:
        capacity = _parse_positive_int(
            metadata["max_link_capacity"], "max_link_capacity", line_num
        )
    return Connection(zone1=zone1, zone2=zone2, max_link_capacity=capacity)


def parse_map(path: Union[str, Path]) -> MapData:
    """Parse a Fly-in map file and return its MapData.

    Args:
        path: Path to the map file.

    Returns:
        A MapData object with drones, zones and connections.

    Raises:
        ParsingError: If the file violates any syntax or semantic rule.
        OSError: If the file cannot be read.
    """
    nb_drones: int | None = None
    zones: dict[str, Zone] = {}
    connections: list[Connection] = []
    seen_pairs: set[frozenset[str]] = set()
    start_seen = False
    end_seen = False
    header_seen = False

    with open(path, "r", encoding="utf-8") as handle:
        for line_num, raw_line in enumerate(handle, start=1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            tokens = line.split()
            keyword = tokens[0]

            if keyword == "nb_drones:":
                if header_seen:
                    raise ParsingError(
                        f"Line {line_num}: 'nb_drones:' may only appear once."
                    )
                if len(tokens) != 2:
                    raise ParsingError(
                        f"Line {line_num}: expected 'nb_drones: <number>'."
                    )
                nb_drones = _parse_positive_int(
                    tokens[1], "nb_drones", line_num
                )
                header_seen = True
                continue

            if not header_seen:
                raise ParsingError(
                    f"Line {line_num}: first non-empty line must be "
                    "'nb_drones: <number>'."
                )

            if keyword in ("start_hub:", "end_hub:", "hub:"):
                is_start = keyword == "start_hub:"
                is_end = keyword == "end_hub:"
                zone = _parse_zone_line(
                    tokens, line_num, is_start=is_start, is_end=is_end
                )
                if zone.name in zones:
                    raise ParsingError(
                        f"Line {line_num}: duplicate zone name "
                        f"'{zone.name}'."
                    )
                if is_start:
                    if start_seen:
                        raise ParsingError(
                            f"Line {line_num}: start_hub defined twice."
                        )
                    start_seen = True
                if is_end:
                    if end_seen:
                        raise ParsingError(
                            f"Line {line_num}: end_hub defined twice."
                        )
                    end_seen = True
                zones[zone.name] = zone
            elif keyword == "connection:":
                conn = _parse_connection_line(tokens, line_num, zones)
                pair = frozenset((conn.zone1, conn.zone2))
                if pair in seen_pairs:
                    raise ParsingError(
                        f"Line {line_num}: duplicate connection "
                        f"'{conn.zone1}-{conn.zone2}'."
                    )
                seen_pairs.add(pair)
                connections.append(conn)
            else:
                raise ParsingError(
                    f"Line {line_num}: unknown keyword '{keyword}'."
                )

    if nb_drones is None:
        raise ParsingError("Missing 'nb_drones:' header.")
    if not start_seen:
        raise ParsingError("Missing 'start_hub:' zone.")
    if not end_seen:
        raise ParsingError("Missing 'end_hub:' zone.")

    return MapData(nb_drones=nb_drones, zones=zones, connections=connections)
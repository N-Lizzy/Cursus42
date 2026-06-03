from pydantic import BaseModel, Field, ValidationError
from datetime import datetime
from typing import Optional


class SpaceStation(BaseModel):
    station_id: str = Field(..., min_length=3, max_length=10)
    name: str = Field(..., min_length=1, max_length=50)
    crew_size: int = Field(..., ge=1, le=20)
    power_level: float = Field(..., ge=0.0, le=100.0)
    oxygen_level: float = Field(..., ge=0.0, le=100.0)
    last_maintenance: datetime = Field(...)
    is_operational: bool = True
    notes: Optional[str] = Field(None, max_length=200)


def main() -> None:
    print("Space Station Data Validation")
    print("========================================")

    print("Valid station created:")
    try:
        station = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=6,
            power_level=85.5,
            oxygen_level=92.3,
            last_maintenance=datetime.now(),
            is_operational=True,
            notes="Routine maintenance completed")

        print(f"ID: {station.station_id}")
        print(f"Name: {station.name}")
        print(f"Crew: {station.crew_size} people")
        print(f"Power: {station.power_level}%")
        print(f"Oxygen: {station.oxygen_level}%")
        if station.is_operational:
            print("Status: Operational")
        else:
            print("Status: Not operational")

    except ValidationError as e:
        error_msg = e.errors()[0]['msg']
        print(error_msg)

    print("\n========================================")
    print("Expected validation error:")
    try:
        invalid_station = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=25,
            power_level=85.5,
            oxygen_level=92.3,
            last_maintenance=datetime.now())

        print(f"ID: {invalid_station.station_id}")
        print(f"Name: {invalid_station.name}")
        print(f"Crew: {invalid_station.crew_size} people")
        print(f"Power: {invalid_station.power_level}%")
        print(f"Oxygen: {invalid_station.oxygen_level}%")
        if invalid_station.is_operational:
            print("Status: Operational")
        else:
            print("Status: Not operational")

    except ValidationError as e:
        error_msg = e.errors()[0]['msg']
        print(error_msg)


if __name__ == "__main__":
    main()

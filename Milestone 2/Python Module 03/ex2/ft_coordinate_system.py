import math


def get_player_pos() -> tuple[float, float, float]:
    while True:
        coords: list[float] = []
        actual: str = ""
        error: bool = False

        position: str = input("Enter new coordinates as floats "
                              "in format 'x,y,z': ")

        if "," not in position:
            print("Invalid syntax")
            continue

        for ch in position:
            if ch == " ":
                continue

            if ch == ",":
                if actual == "":
                    print("Invalid syntax")
                    error = True
                    break
                try:
                    coords.append(float(actual))
                except ValueError as e:
                    print(f"Error on parameter '{actual}': {e}")
                    error = True
                    break
                actual = ""
            else:
                actual += ch

        if error:
            continue

        try:
            coords.append(float(actual))
        except ValueError as e:
            print(f"Error on parameter '{actual}': {e}")
            continue

        return (coords[0], coords[1], coords[2])


if __name__ == "__main__":
    print("=== Game Coordinate System ===\n")

    print("Get a first set of coordinates")
    coord1: tuple[float, float, float] = get_player_pos()

    print(f"Got a first tuple: {coord1}")
    print(f"It includes: X={coord1[0]}, Y={coord1[1]}, Z={coord1[2]}")
    print(f"Distance to center: "
          f"{round(math.sqrt(coord1[0]**2 + coord1[1]**2 + coord1[2]**2), 4)}")

    print("\nGet a second set of coordinates")
    coord2: tuple[float, float, float] = get_player_pos()

    dist: float = math.sqrt(
        (coord2[0] - coord1[0])**2 +
        (coord2[1] - coord1[1])**2 +
        (coord2[2] - coord1[2])**2)

    print(f"Distance between the 2 sets of coordinates: {round(dist, 4)}")

def check_plant_health(plant_name: str, water_level: int,
                       sunlight_hours: int) -> None:
    if plant_name == "":
        raise ValueError("Error: Plant name cannot be empty!\n")
    if water_level > 10:
        raise ValueError(f"Error: Water level {water_level} is too high "
                         f"(max 10)\n")
    if water_level < 1:
        raise ValueError(f"Error: Water level {water_level} is too low "
                         f"(min 1)\n")
    if sunlight_hours > 12:
        raise ValueError(f"Error: Sunlight hours {sunlight_hours} is too high "
                         f"(max 12)\n")
    if sunlight_hours < 2:
        raise ValueError(f"Error: Sunlight hours {sunlight_hours} is too low "
                         f"(min 2)\n")
    print(f"Plant '{plant_name}' is healthy!\n")


def test_plant_checks() -> None:
    print("=== Garden Plant Health Checker ===\n")

    print("Testing good values...")
    check_plant_health("tomato", 5, 5)

    print("Testing empty plant name...")
    try:
        check_plant_health("", 5, 5)
    except ValueError as e:
        print(e)

    print("Testing bad water level...")
    try:
        check_plant_health("tomato", 15, 5)
    except ValueError as e:
        print(e)

    print("Testing bad sunlight hours...")
    try:
        check_plant_health("tomato", 5, 0)
    except ValueError as e:
        print(e)

    print("All error raising tests completed!")


if __name__ == "__main__":
    test_plant_checks()

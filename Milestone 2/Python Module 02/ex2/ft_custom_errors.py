class GardenError(Exception):
    pass


class PlantError(GardenError):
    pass


class WaterError(GardenError):
    pass


def test_garden_errors() -> None:
    try:
        print("Testing PlantError...")
        raise PlantError("The tomato plant is wilting!")
    except PlantError as error:
        print(f"Caught PlantError: {error}\n")

    try:
        print("Testing WaterError...")
        raise WaterError("Not enough water in the tank!")
    except WaterError as error:
        print(f"Caught WaterError: {error}\n")

    print("Testing catching all garden errors...")
    try:
        raise GardenError("The tomato plant is wilting!")
    except GardenError as error:
        print(f"Caught a garden error: {error}")

    try:
        raise GardenError("Not enough water in the tank!")
    except GardenError as error:
        print(f"Caught a garden error: {error}\n")


if __name__ == "__main__":
    print("=== Custom Garden Errors Demo ===\n")
    test_garden_errors()
    print("All custom error types work correctly!")

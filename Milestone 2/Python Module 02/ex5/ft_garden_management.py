class GardenError(Exception):
    pass


class PlantError(GardenError):
    pass


class WaterError(GardenError):
    pass


class GardenManager:
    def __init__(self):
        self.plants = {}

    def add_plant(self, plant_name: str, water_level: int,
                  sunlight_hours: int) -> None:
        try:
            if plant_name == "":
                raise PlantError("Plant name cannot be empty!")
            self.plants[plant_name] = {
                "water": water_level,
                "sunlight": sunlight_hours}
            print(f"Added {plant_name} successfully")
        except PlantError as e:
            print(f"Error adding plant: {e}\n")

    def water_plants(self) -> None:
        try:
            print("Opening watering system")
            for plant in self.plants:
                if plant is None:
                    raise WaterError("Cannot water None - invalid plant!")
                print(f"Watering {plant} - success")
        except WaterError as e:
            print(f"Error: {e}")
        finally:
            print("Closing watering system (cleanup)\n")

    def check_plant_health(self) -> None:
        for plant_name, info in self.plants.items():
            try:
                water = info["water"]
                sunlight = info["sunlight"]

                if water > 10:
                    raise ValueError(f"Error: Water level {water} "
                                     f"is too high (max 10)\n")
                if water < 1:
                    raise ValueError(f"Error: Water level {water} "
                                     f"is too low (min 1)\n")
                if sunlight > 12:
                    raise ValueError(f"Error: Sunlight hours {sunlight} "
                                     f"is too high (max 12)\n")
                if sunlight < 2:
                    raise ValueError(f"Error: Sunlight hours {sunlight} "
                                     f"is too low (min 2)\n")
                print(f"{plant_name}: healthy (water: {water}, "
                      f"sun: {sunlight})")
            except ValueError as e:
                print(f"Error checking {plant_name}: {e}")

    def garden_error(self) -> None:
        raise WaterError("Not enough water in tank")


def test_garden_management() -> None:
    print("=== Garden Management System ===\n")
    manager = GardenManager()

    print("Adding plants to garden...")
    manager.add_plant("tomato", 5, 8)
    manager.add_plant("lettuce", 15, 5)
    manager.add_plant("", 1, 4)

    print("Watering plants...")
    manager.water_plants()

    print("Checking plant health...")
    manager.check_plant_health()

    print("Testing error recovery...")
    try:
        manager.garden_error()
    except GardenError as e:
        print(f"Caught GardenError: {e}")
        print("System recovered and continuing...\n")

    print("Garden management system test complete!")


if __name__ == "__main__":
    test_garden_management()

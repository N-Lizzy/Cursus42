class Plant:
    def __init__(self, name: str, height: int) -> None:
        self.name = name
        self.height = height
        self.initial_height: int = height

    def grow(self) -> None:
        self.height += 1
        print(f"{self.name} grew 1cm")

    def growth(self) -> int:
        return self.height - self.initial_height

    def type_name(self) -> str:
        return "regular"

    def get_info(self) -> str:
        return (f"{self.name}: {self.height}cm")


class FloweringPlant(Plant):
    def __init__(self, name: str, height: int, color: str) -> None:
        super().__init__(name, height)
        self.color = color

    def type_name(self) -> str:
        return "flowering"

    def get_info(self) -> str:
        return (f"{self.name}: {self.height}cm, {self.color} flowers "
                f"(blooming)")


class PrizeFlower(FloweringPlant):
    def __init__(self, name: str, height: int, color: str,
                 prize_points: int) -> None:
        super().__init__(name, height, color)
        self.prize_points = prize_points

    def type_name(self) -> str:
        return "prize flowers"

    def get_info(self) -> str:
        return (f"{self.name}: {self.height}cm, {self.color} flowers"
                f" (blooming), Prize points: {self.prize_points}")


class GardenManager:
    total_gardens: int = 0

    def __init__(self, owner: str):
        self.owner = owner
        self.plants: list[Plant] = []
        GardenManager.total_gardens += 1

    @classmethod
    def create_garden_network(cls) -> None:
        print(f"Total gardens managed: {cls.total_gardens}")

    @staticmethod
    def check_height(height: int) -> bool:
        return height >= 0

    def add_plant(self, plant: Plant):
        if not self.check_height(plant.height):
            print(f"Invalid height for {plant.name}")
            return
        self.plants.append(plant)
        print(f"Added {plant.name} to {self.owner}'s garden")

    def grow_plants(self) -> None:
        print(f"{self.owner} is helping all plants grow...")
        for plant in self.plants:
            plant.grow()

    class GardenStats:
        @staticmethod
        def total_plants(plants: list[Plant]) -> int:
            total_plants: int = 0
            for plant in plants:
                total_plants += 1
            return total_plants

        @staticmethod
        def total_growth(plants: list[Plant]) -> int:
            total_height: int = 0
            for plant in plants:
                total_height += (plant.height - plant.initial_height)
            return total_height

        @staticmethod
        def count_types(plants: list[Plant], type: str) -> int:
            total_type: int = 0
            for plant in plants:
                if (plant.type_name() == type):
                    total_type += 1
            return total_type

    def garden_report(self) -> None:
        print(f"=== {self.owner}'s Garden Report ===")
        print("Plants in garden: ")
        for plant in self.plants:
            print(f"- {plant.get_info()}")
        print("")
        print(f"Plants added: {self.GardenStats.total_plants(self.plants)}, "
              f"Total growth: {self.GardenStats.total_growth(self.plants)}cm")
        print(f"Plant types: "
              f"{self.GardenStats.count_types(self.plants, 'regular')}"
              f" regular, "
              f"{self.GardenStats.count_types(self.plants, 'flowering')}"
              f" flowering, "
              f"{self.GardenStats.count_types(self.plants, 'prize flowers')}"
              f" prize flowers")

    def calculate_score(self) -> int:
        final_score: int = 0
        for plant in self.plants:
            final_score += plant.height
            if plant.type_name() == "prize flowers":
                final_score += plant.prize_points
        return final_score


oak = Plant("Oak Tree", 100)
rose = FloweringPlant("Rose", 25, "red")
sunflower = PrizeFlower("Sunflower", 50, "yellow", 10)

if __name__ == "__main__":
    print("=== Garden Management System Demo ===")
    print("")

    alice = GardenManager("Alice")
    alice.add_plant(oak)
    alice.add_plant(rose)
    alice.add_plant(sunflower)

    print("")
    alice.grow_plants()

    print("")
    alice.garden_report()

    print("")
    bob = GardenManager("Bob")
    print(f"Garden scores - {alice.owner}: {alice.calculate_score()}, "
          f"{bob.owner}: {bob.calculate_score()}")
    GardenManager.create_garden_network()

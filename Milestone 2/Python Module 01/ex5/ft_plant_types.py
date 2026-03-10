class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age


class Flower(Plant):
    def __init__(self, name: str, height: int, age: int, color: str) -> None:
        super().__init__(name, height, age)
        self.color = color

    def bloom(self) -> None:
        print(f"{self.name} is blooming beautifully!")

    def get_info(self) -> None:
        print(f"{self.name} (Flower): {self.height}cm, {self.age} "
              f"days, {self.color} color")


class Tree(Plant):
    def __init__(self, name: str, height: int, age: int,
                 trunk_diameter: int) -> None:
        super().__init__(name, height, age)
        self.trunk_diameter = trunk_diameter

    def produce_shade(self) -> None:
        shade = int((self.height * self.trunk_diameter) / 320)
        print(f"{self.name} provides {shade} square meters of shade")

    def get_info(self) -> None:
        print(f"{self.name} (Tree): {self.height}cm, {self.age} "
              f"days, {self.trunk_diameter}cm diameter")


class Vegetable(Plant):
    def __init__(self, name: str, height: int, age: int, harvest_season: str,
                 nutritional_value: str) -> None:
        super().__init__(name, height, age)
        self.harvest_season = harvest_season
        self.nutritional_value = nutritional_value

    def get_info(self) -> None:
        print(f"{self.name} (Vegetable): {self.height}cm, {self.age} days,"
              f"{self.harvest_season} harvest")
        print(f"{self.name} is rich in {self.nutritional_value}")


rose = Flower("Rose", 25, 30, "red")
sunflower = Flower("Sunflower", 150, 40, "yellow")

oak = Tree("Oak", 500, 1825, 50)
maple = Tree("Maple", 480, 2100, 45)

tomato = Vegetable("Tomato", 80, 90, "summer", "vitamin C")
spinach = Vegetable("Spinach", 40, 45, "spring", "iron")

if __name__ == "__main__":
    print("=== Garden Plant Types ===")
    print("")
    rose.get_info()
    rose.bloom()
    print("")
    oak.get_info()
    oak.produce_shade()
    print("")
    tomato.get_info()

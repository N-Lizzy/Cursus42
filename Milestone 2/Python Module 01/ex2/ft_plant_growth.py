class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    def grow(self) -> None:
        self.height += 1

    def age_grow(self) -> None:
        self.age += 1

    def get_info(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.age} days old")


plant = Plant("Rose", 25, 30)
week: int = 6
i: int = 0

if __name__ == "__main__":
    print("=== Day 1 ===")
    plant.get_info()
    while i < week:
        plant.grow()
        plant.age_grow()
        i += 1
    print("=== Day 7 ===")
    plant.get_info()
    print(f"Growth this week: +{i}cm")

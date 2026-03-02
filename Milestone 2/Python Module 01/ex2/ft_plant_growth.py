class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age

    def grow(self):
        self.height += 1

    def age_grow(self):
        self.age += 1

    def get_info(self):
        print(f"{self.name}: {self.height}cm, {self.age} days old")


plant = Plant("Rose", 25, 30)
week = 6
i = 0

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

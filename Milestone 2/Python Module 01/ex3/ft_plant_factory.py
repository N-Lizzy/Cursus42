class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age

    def get_info(self):
        print(f"Created: {self.name} ({self.height}cm, {self.age} days)")


plants_list = [
    ("Rose", 25, 30),
    ("Oak", 200, 365),
    ("Cactus", 5, 90),
    ("Sunflower", 80, 45),
    ("Fern", 15, 120)]
i = 0

if __name__ == "__main__":
    print("=== Plant Factory Output ===")
    for plant in plants_list:
        new_plant = Plant(plant[0], plant[1], plant[2])
        new_plant.get_info()
        i += 1
print(" ")
print(f"Total plants created: {i}")

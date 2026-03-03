class SecurePlant:
    def __init__(self, name):
        self.name = name
        self.height = 0
        self.age = 0

    def set_height(self, height):
        if height < 0:
            print(f"Invalid operation attempted: {height}cm [REJECTED]")
            print("Security: Negative height rejected")
        else:
            self.height = height
            print(f"Height updated: {height}cm [OK]")

    def set_age(self, age):
        if age < 0:
            print(f"Invalid operation attempted: {age} days [REJECTED]")
            print("Security: Negative age rejected")
        else:
            self.age = age
            print(f"Age updated: {age} days [OK]")

    def get_height(self):
        return self.height

    def get_age(self):
        return self.age


plant = SecurePlant("Rose")

if __name__ == "__main__":
    print(f"Plant created: {plant.name}")
    plant.set_height(25)
    plant.set_age(30)
    print("")
    plant.set_height(-5)
    print("")
    print(f"Current plant: {plant.name} ({plant.get_height()}cm, "
          f"{plant.get_age()} days)")

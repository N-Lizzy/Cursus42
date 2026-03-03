class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age
        
class Flower(Plant):
	def __init__(self, name, height, age, color):
		super().__init__(name, height, age)
		self.color = color

	def bloom(self):
        	print(f"{self.name} is blooming beautifully!")
        
	def get_info(self):
		print(f"{self.name} (Flower): {self.height}cm, {self.age} days, {self.color} color")

class Tree(Plant):
	def __init__(self, name, height, age, trunk_diameter):
		super().__init__(name, height, age)
		self.trunk_diameter = trunk_diameter
	
	def produce_shade(self):
		shade = int((self.height * self.trunk_diameter) / 320)
		print(f"{self.name} provides {shade} square meters of shade")
		
	def get_info(self):
    		print(f"{self.name} (Tree): {self.height}cm, {self.age} days, {self.trunk_diameter}cm diameter")
	

class Vegetable(Plant):
	def __init__(self, name, height, age, harvest_season, nutritional_value):
		super().__init__(name, height, age)
		self.harvest_season = harvest_season
		self.nutritional_value = nutritional_value
	
	def get_info(self):
	    	print(f"{self.name} (Vegetable): {self.height}cm, {self.age} days, {self.harvest_season} harvest")
	    	print(f"{self.name} is rich in {self.nutritional_value}")

flower1 = Flower("Rose", 25, 30, "red")
flower2 = Flower("Sunflower", 150, 40, "yellow")

tree1 = Tree("Oak", 500, 1825, 50)
tree2 = Tree("Maple", 480, 2100, 45)

vegetable1 = Vegetable("Tomato", 80, 90, "summer", "vitamin C")
vegetable2 = Vegetable("Spinach", 40, 45, "spring", "iron")

if __name__ == "__main__":
	print("=== Garden Plant Types ===")
	print("")
	flower1.get_info()
	flower1.bloom()
	print("")
	tree1.get_info()
	tree1.produce_shade()
	print("")
	vegetable1.get_info()
	
	

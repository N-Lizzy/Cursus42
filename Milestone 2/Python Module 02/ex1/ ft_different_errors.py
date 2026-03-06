def garden_operations(test_type):
	if test_type == "value":
		try:
			print("Testing ValueError...")
			int("abc")
		except ValueError:
			print("Caught ValueError: invalid literal for int()\n")

	elif test_type == "zero":
		try:
			print("Testing ZeroDivisionError...")
			10 / 0
		except ZeroDivisionError:
			print("Caught ZeroDivisionError: division by zero\n")

	elif test_type == "file":
		try:
			print("Testing FileNotFoundError...")
			open("missing.txt")
		except FileNotFoundError:
			print("FileNotFoundError: No such file 'missing.txt'\n")

	elif test_type == "key":
		try:
			print("Testing KeyError...")
			plants = {}
			print(plants["sunflower"])
		except KeyError:
			print("Caught KeyError: 'missing\_plant'")

	elif test_type == "multiple":
		try:
			print("Testing multiple error catch...")
			int("abc")
			10 / 10
		except (ValueError, ZeroDivisionError):
			print("Caught an error, but program continues!")

def test_error_types():
    print("=== Garden Error Testing ===")
    garden_operations("value")
    garden_operations("zero")
    garden_operations("file")
    garden_operations("key")
	garden_operations("multiple")
    print("Program continues running after all errors!")

if __name__ == "__main__":
	def test_error_types()
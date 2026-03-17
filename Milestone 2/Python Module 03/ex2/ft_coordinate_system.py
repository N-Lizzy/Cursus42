import math

origin_pos: tuple = (0, 0, 0)
test_pos: tuple = (10, 20, 5)

if __name__ == "__main__":
    print("=== Game Coordinate System ===\n")

    print(f"Position created: {test_pos}")
x1, y1, z1 = origin_pos
x2, y2, z2 = test_pos

distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)

import sys

inventory: dict[str, int] = {}
order: list[str] = []

if __name__ == "__main__":
    print("=== Inventory System Analysis ===")

    for arg in sys.argv[1:]:
        index: int = 0
        while index < len(arg) and arg[index] != ':':
            index += 1

        if index == len(arg):
            print(f"Error - invalid parameter '{arg}")
            continue

        check: int = index + 1
        while check < len(arg):
            if arg[check] == ':':
                print(f"Error - invalid parameter '{arg}'")
                break
            check += 1
        else:
            item: str = arg[:index]
            qty_str: str = arg[index+1:]

            try:
                qty: int = int(qty_str)
            except ValueError:
                print(f"Quantity error for '{item}': invalid number")
                continue

            if item in inventory:
                print(f"Redundant item '{item}' - discarding")
                continue

            inventory[item] = qty
            order.append(item)

    print("Got inventory: " + str(inventory))

    items: list[str] = list(inventory.keys())
    print("Item list: " + str(items))

    total: int = 0
    for v in inventory.values():
        total += v
    print("Total quantity of the " + str(len(items)) + " items: " + str(total))

    for item in items:
        percent: float = 0
        if total != 0:
            percent = round(inventory[item] * 100 / total, 1)
        print("Item " + item + " represents " + str(percent) + "%")

    most_item: str = order[0] if order else ""
    least_item: str = order[0] if order else ""

    for item in order:
        if inventory[item] > inventory[most_item]:
            most_item = item
        if inventory[item] < inventory[least_item]:
            least_item = item

    print(f"Item most abundant: {most_item} with "
          f"quantity {inventory[most_item]}")
    print(f"Item least abundant: {least_item} with "
          f"quantity {inventory[least_item]}")

    inventory["magic_item"] = 1
    print("Updated inventory: " + str(inventory))

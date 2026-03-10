def ft_count_harvest_recursive() -> None:
    days: int = int(input("Days until harvest: "))

    def print_days(i):
        if i > days:
            print("Harvest time!")
            return
        print(f"Day {i}")
        print_days(i + 1)

    print_days(1)

def check_temperature(temp_str: str) -> None:
    try:
        temp_int: int = int(temp_str)
    except ValueError:
        print(f"Testing Temperature: {temp_str}")
        print(f"Error: '{temp_str}' is not a valid number\n")
        return

    if temp_int < 0:
        print(f"Testing Temperature: {temp_str}")
        print(f"Error: {temp_str}ºC is too cold for plants (min 0ºC)\n")

    elif temp_int > 40:
        print(f"Testing Temperature: {temp_str}")
        print(f"Error: {temp_str}ºC os too hot for plants (max 40ºC)\n")

    else:
        print(f"Testing Temperature: {temp_str}")
        print(f"Temperature {temp_str}ºC is perfect for plants!\n")


def test_temperature_input() -> None:
    print("=== Garden Temperature Checker ===\n")
    check_temperature("25")
    check_temperature("abc")
    check_temperature("100")
    check_temperature("-50")
    print("All tests completed - program didn't crash!")


if __name__ == "__main__":
    test_temperature_input()

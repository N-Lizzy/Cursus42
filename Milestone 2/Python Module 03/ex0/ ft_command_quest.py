import sys

if __name__ == "__main__":
    args_len: int = len(sys.argv)
    i: int = 1

    print("=== Command Quest ===")

    if args_len == 1:
        print("No arguments provided!")

    print(f"Program name: {sys.argv[0]}")

    if args_len > 1:
        print(f"Arguments received: {args_len - 1}")
        for argument in sys.argv[1:]:
            print(f"Arument {i}: {argument}")
            i += 1

    print(f"Total arguments: {args_len}")

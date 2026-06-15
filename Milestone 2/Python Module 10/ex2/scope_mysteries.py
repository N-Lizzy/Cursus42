from collections.abc import Callable


def mage_counter() -> Callable:
    count = 0

    def counter():
        nonlocal count
        count += 1
        return count
    return counter


def spell_accumulator(initial_power: int) -> Callable:
    count = initial_power

    def accumulator(amount: int) -> int:
        nonlocal count
        count += amount
        return count
    return accumulator


def enchantment_factory(enchantment_type: str) -> Callable:
    def enchantment_out(item: str) -> str:
        return f"{enchantment_type} {item}"
    return enchantment_out


def memory_vault() -> dict[str, Callable]:
    memory = {}

    def store(key, value) -> None:
        memory[key] = value

    def recall(key) -> any:
        return memory.get(key, "Memory not found")

    return {"store": store, "recall": recall}


def main() -> None:
    print("Testing mage counter...")
    counter_a = mage_counter()
    counter_b = mage_counter()

    print(f"counter_a call 1: {counter_a()}")
    print(f"counter_a call 2: {counter_a()}")
    print(f"counter_b call 1: {counter_b()}\n")

    print("Testing spell accumulator...")
    spell = spell_accumulator(100)
    print(f"Base 100, add 20: {spell(20)}")
    print(f"Base 100, add 30: {spell(30)}\n")

    print("Testing enchantment factory...")
    flaming = enchantment_factory("Flaming")
    frozen = enchantment_factory("Frozen")
    print(f"{flaming('Sword')}")
    print(f"{frozen('Shield')}\n")

    print("Testing memory vault...")
    vault = memory_vault()
    vault["store"]("secret", 42)
    print("Store 'secret' = 42")
    print(f"Recall 'secret': {vault['recall']('secret')}")
    print(f"Recall 'unknown': {vault['recall']('unknown')}")


if __name__ == "__main__":
    main()

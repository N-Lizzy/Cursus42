from collections.abc import Callable


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:
    def combined_spell(target: str, power: int) -> tuple[str, str]:
        return (spell1(target, power), spell2(target, power))
    return combined_spell


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:
    def amplified_spell(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)
    return amplified_spell


def conditional_caster(condition: Callable, spell: Callable) -> Callable:
    def cast_spell(target: str, power: int) -> str:
        if condition(target, power):
            return spell(target, power)
        else:
            return "Spell fizzled"
    return cast_spell


def min_power(target, power) -> bool:
    return power >= 50


def spell_sequence(spells: list[Callable]) -> Callable:
    def sequence(target: str, power: int) -> list[str]:
        return [spell(target, power) for spell in spells]
    return sequence


def fireball(target: str, power: int) -> str:
    return f"Fireball hits {target} for {power} damage"


def heal(target: str, power: int) -> str:
    return f"Heal restores {target} for {power} HP"


def main() -> None:
    print("Testing spell combiner...")
    combined = spell_combiner(fireball, heal)
    result = combined("Dragon", 10)
    print(f"Combined spell result: {result[0]}, {result[1]}\n")

    print("Testing power amplifier...")
    normal_fireball = fireball("Dragon", 10)
    mega_fireball = power_amplifier(fireball, 3)
    result = mega_fireball("Dragon", 10)
    print(f"Original: {normal_fireball}, Amplified: {result}\n")

    print("Testing conditional caster...")
    conditional_fireball = conditional_caster(min_power, fireball)
    false_result = conditional_fireball("Dragon", 10)
    true_result = conditional_fireball("Dragon", 60)
    print(f"(False) Low power (10): {false_result}")
    print(f"(True) High power (60): {true_result}\n")

    print("Testing spell sequence...")
    combo = spell_sequence([fireball, heal])
    result = combo("Dragon", 10)
    for i, spell_result in enumerate(result, 1):
        print(f"  Spell {i}: {spell_result}")


if __name__ == "__main__":
    main()

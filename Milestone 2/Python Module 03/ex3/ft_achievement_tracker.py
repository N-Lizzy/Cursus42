import random


def gen_player_achievements() -> set[str]:
    achievements: list[str] = [
        "Crafting Genius", "World Savior", "Master Explorer",
        "Collector Supreme", "Untouchable", "Boss Slayer", "Strategist",
        "Unstoppable", "Speed Runner", "Survivor", "Treasure Hunter",
        "First Steps", "Sharp Mind", "Hidden Path Finder"]

    num_archvs: int = random.randint(3, len(achievements))
    return set(random.sample(achievements, num_archvs))


if __name__ == "__main__":
    print("=== Achievement Tracker System ===\n")

    players: dict[str, set[str]] = {
        "Alice": gen_player_achievements(),
        "Bob": gen_player_achievements(),
        "Charlie": gen_player_achievements(),
        "Dylan": gen_player_achievements()
    }

    for name, achv in players.items():
        print(f"Player {name}: {achv}")

    all_achvs: set[str] = set()
    for achv in players.values():
        all_achvs = all_achvs.union(achv)
    print(f"\nAll distinct achievements: {all_achvs}")

    common_achvs: set[str] = set.intersection(*players.values())
    print(f"\nCommon achievements: {common_achvs}\n")

    for name, achv in players.items():
        others = set.union(*(players[p] for p in players if p != name))
        unique = achv.difference(others)
        print(f"Only {name} has: {unique}")

    print("")
    for name, achv in players.items():
        missing = all_achvs.difference(achv)
        print(f"{name} is missing: {missing}")

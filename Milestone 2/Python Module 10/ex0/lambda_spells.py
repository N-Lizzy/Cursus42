def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    return sorted(artifacts, key=lambda x: x["power"], reverse=True)


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    return list(filter(lambda mage: mage["power"] >= min_power, mages))


def spell_transformer(spells: list[str]) -> list[str]:
    return list(map(lambda spell: "* " + spell + " *", spells))


def mage_stats(mages: list[dict]) -> dict:
    return {
        "max_power": max(mages, key=lambda mage: mage["power"])["power"],
        "min_power": min(mages, key=lambda mage: mage["power"])["power"],
        "avg_power": round(sum(map(lambda mage: mage["power"], mages))
                           / len(mages), 2)}


def main() -> None:
    artifacts: list[dict] = (
            {"name": "Crystal Orb", "power": 85, "type": "Orb"},
            {"name": "Fire Staff", "power": 92, "type": "Staff"})

    mages: list[dict] = (
            {"name": "Obi-Wan Kenobi", "power": 85, "element": "Water"},
            {"name": "Anakin Skywalker", "power": 45, "element": "Fire"})

    spells: list[str] = ("fireball", "heal", "shield")

    print("Testing artifact sorter...")
    sort_artfs = artifact_sorter(artifacts)
    print(f"{sort_artfs[0]['name']} ({sort_artfs[0]['power']} power) comes "
          f"before {sort_artfs[1]['name']} ({sort_artfs[1]['power']} power)")

    print("\nTesting power filter...")
    filter_mages = power_filter(mages, 50)
    print(f"The mage with 50 >= power is: {filter_mages[0]['name']} "
          f"({filter_mages[0]['power']} power)")

    print("\nTesting spell transformer...")
    transform_spells = spell_transformer(spells)
    print(f"{transform_spells}")

    print("\nTesting mage stats...")
    stats = mage_stats(mages)
    print(f"Max: {stats['max_power']}, Min: {stats['min_power']}, "
          f"Avg: {stats['avg_power']}")


if __name__ == "__main__":
    main()

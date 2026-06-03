def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    sorted_artifacts = sorted(artifacts, key=lambda x: x["power"], reverse=True)

# def power_filter(mages: list[dict], min_power: int) -> list[dict]:


# def spell_transformer(spells: list[str]) -> list[str]:


# def mage_stats(mages: list[dict]) -> dict:


def main() -> None:
    artifacts: list[dict] = (
            {"name": "test",
             "power": 6,
             "type": "test"},
            {"name": "test1",
             "power": 2,
             "type": "test"})


if __name__ == "__main__":
    main()

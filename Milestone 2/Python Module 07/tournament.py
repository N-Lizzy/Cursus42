from ex0 import FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import NormalStrategy, AggressiveStrategy, DefensiveStrategy
from ex0.factory import CreatureFactory
from ex2.strategy import BattleStrategy
from ex2.exceptions import InvalidStrategyError


def battle(factory1: CreatureFactory, strategy1: BattleStrategy,
           factory2: CreatureFactory, strategy2: BattleStrategy) -> bool:

    creature1 = factory1.create_base()
    creature2 = factory2.create_base()

    print("* Battle *")
    print(creature1.describe())
    print("vs.")
    print(creature2.describe())
    print("now fight!")

    try:
        strategy1.act(creature1)
        strategy2.act(creature2)
        return True
    except InvalidStrategyError as e:
        print(f"Battle error, aborting tournament: {e}")
        return False


def tournament(opponents: list[tuple[CreatureFactory, BattleStrategy]],
               number: int) -> None:

    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved")
    print("")

    for i in range(len(opponents)):
        for j in range(i + 1, len(opponents)):
            factory1, strategy1 = opponents[i]
            factory2, strategy2 = opponents[j]
            success = battle(factory1, strategy1, factory2, strategy2)
            if not success:
                return
            print()


if __name__ == "__main__":
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()
    healing_factory = HealingCreatureFactory()
    transform_factory = TransformCreatureFactory()

    normal = NormalStrategy()
    aggressive = AggressiveStrategy()
    defensive = DefensiveStrategy()

    print("Tournament 0 (basic)")
    print("[ (Flameling+Normal), (Healing+Defensive) ]")
    opponents_0 = [
        (flame_factory, normal),
        (healing_factory, defensive)]
    tournament(opponents_0, 0)

    print("Tournament 1 (error)")
    print("[ (Flameling+Aggressive), (Healing+Defensive) ]")
    opponents_1 = [
        (flame_factory, aggressive),
        (healing_factory, defensive)]
    tournament(opponents_1, 1)
    print("")

    print("Tournament 2 (multiple)")
    print("[ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ]")
    opponents_2 = [
        (aqua_factory, normal),
        (healing_factory, defensive),
        (transform_factory, aggressive)]
    tournament(opponents_2, 2)

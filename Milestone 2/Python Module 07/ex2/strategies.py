from ex0.creature import Creature
from ex1.capabilities import HealCapability, TransformCapability
from ex2.strategy import BattleStrategy
from ex2.exceptions import InvalidStrategyError


class NormalStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return True

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise InvalidStrategyError(creature.name, "normal")
        print(creature.attack())


class AggressiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, TransformCapability)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise InvalidStrategyError(creature.name, "aggressive")

        transform_creature = creature
        print(transform_creature.transform())
        print(transform_creature.attack())
        print(transform_creature.revert())


class DefensiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, HealCapability)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise InvalidStrategyError(creature.name, "defensive")

        heal_creature = creature
        print(heal_creature.attack())
        print(heal_creature.heal("itself"))

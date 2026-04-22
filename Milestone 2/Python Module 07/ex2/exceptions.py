class InvalidStrategyError(Exception):
    def __init__(self, creature_name: str, strategy_name: str) -> None:
        self.creature_name = creature_name
        self.strategy_name = strategy_name
        message = (
            f"Invalid Creature '{creature_name}' "
            f"for this {strategy_name} strategy")
        super().__init__(message)

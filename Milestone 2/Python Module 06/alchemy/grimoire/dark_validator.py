from .dark_spellbook import dark_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    allowed = dark_spell_allowed_ingredients()
    ingredient_list = [ing.strip().lower() for ing in ingredients.split(",")]
    allowed_lower = [ing.lower() for ing in allowed]

    is_valid = any(ing in allowed_lower for ing in ingredient_list)

    status = "VALID" if is_valid else "INVALID"
    return f"{ingredients} - {status}"

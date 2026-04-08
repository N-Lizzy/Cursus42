def validate_ingredients(ingredients: str) -> str:
    from .light_spellbook import light_spell_allowed_ingredients

    allowed = light_spell_allowed_ingredients()
    ingredient_list = [ing.strip().lower() for ing in ingredients.split(",")]
    allowed_lower = [ing.lower() for ing in allowed]

    is_valid = any(ing in allowed_lower for ing in ingredient_list)

    status = "VALID" if is_valid else "INVALID"
    return f"{ingredients} - {status}"

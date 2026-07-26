def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:
    seed_type = str.capitalize(seed_type)
    if (unit == "packets"):
        unit = f"{quantity} packets available"
    elif (unit == "grams"):
        unit = f"{quantity} grams total"
    elif (unit == "area"):
        unit = f"covers {quantity} square meters"
    else:
        print("Unknown unit type")
        return
    print(f"{seed_type} seeds: {unit}")

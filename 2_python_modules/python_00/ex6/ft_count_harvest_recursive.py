def ft_count_harvest_recursive(days: int | None = None, cursor: int = 1) -> None:
    if (days is None):
        days = int(input("Days until harvest: "))
    if (cursor > days):
        print("Harvest time!")
        return
    print(f"Day {cursor}")
    ft_count_harvest_recursive(days, cursor + 1)

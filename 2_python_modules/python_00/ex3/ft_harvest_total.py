def ft_harvest_total() -> None:
    total = 0
    for i in [1, 2, 3]:
        total += int(input(f"Day {i} harvest: "))
    print(f"Total harvest: {total}")

import random


name: str

if __name__ == "__main__":
    print("=== Game Data Alchemist ===\n")

    players: list[str] = ['Alice', 'bob', 'Charlie', 'dylan', 'Emma',
                          'Gregory', 'john', 'kevin', 'Liam']
    print(f"Initial list of players: {players}")

    all_capitalized: list[str] = []
    for name in players:
        if name == "":
            all_capitalized.append(name)
            continue
        first: str = name[0]
        if first == 'a':
            first = 'A'
        elif first == 'b':
            first = 'B'
        elif first == 'c':
            first = 'C'
        elif first == 'd':
            first = 'D'
        elif first == 'e':
            first = 'E'
        elif first == 'f':
            first = 'F'
        elif first == 'g':
            first = 'G'
        elif first == 'h':
            first = 'H'
        elif first == 'i':
            first = 'I'
        elif first == 'j':
            first = 'J'
        elif first == 'k':
            first = 'K'
        elif first == 'l':
            first = 'L'
        elif first == 'm':
            first = 'M'
        elif first == 'n':
            first = 'N'
        elif first == 'o':
            first = 'O'
        elif first == 'p':
            first = 'P'
        elif first == 'q':
            first = 'Q'
        elif first == 'r':
            first = 'R'
        elif first == 's':
            first = 'S'
        elif first == 't':
            first = 'T'
        elif first == 'u':
            first = 'U'
        elif first == 'v':
            first = 'V'
        elif first == 'w':
            first = 'W'
        elif first == 'x':
            first = 'X'
        elif first == 'y':
            first = 'Y'
        elif first == 'z':
            first = 'Z'
        new_name = first
        for letra in name[1:]:
            new_name += letra
        all_capitalized.append(new_name)
    print(f"New list with all names capitalized: {all_capitalized}")

    capitalized_only: list[str] = []
    for name in players:
        if name != "" and name[0] in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            capitalized_only.append(name)
    print(f"New list of capitalized names only: {capitalized_only}\n")

    score_dict: dict[str, int] = {}
    for name in all_capitalized:
        score_dict[name] = random.randint(1, 1000)
    print(f"Score dict: {score_dict}")

    total_score: float = 0
    for name in score_dict:
        total_score += score_dict[name]
    average_score = total_score / len(score_dict)
    print(f"Score average is {round(average_score, 2)}")

    high_scores: dict[str, float] = {}
    for name in score_dict:
        if score_dict[name] > average_score:
            high_scores[name] = score_dict[name]
    print(f"High scores: {high_scores}")

import sys

if __name__ == "__main__":
    args: list[str] = sys.argv
    arg_len: int = len(sys.argv)
    i: int = 1
    scores: list[int] = []

    print("=== Player Score Analytics ===")

    if arg_len == 1:
        print("No scores provided. Usage: python3 ft_score_analytics.py "
              "<score1> <score2> ...")

    if arg_len > 1:
        for arg in args[1:]:
            try:
                scores.append(int(arg))
            except ValueError:
                print(f"Invalid parameter: '{arg}'")

    if scores:
        total_players: int = len(scores)
        total_scores: int = sum(scores)
        average_scores: int = total_scores / total_players
        high_score: int = max(scores)
        low_score: int = min(scores)
        Score_range: int = high_score - low_score

        print(f"Total players: {total_players}")
        print(f"Total score: {total_scores}")
        print(f"Average score: {average_scores}")
        print(f"High score: {high_score}")
        print(f"Low score: {low_score}")
        print(f"Score range: {Score_range}")
    else:
        print("No scores provided. Usage: python3 ft_score_analytics.py "
              "<score1> <score2> ...")

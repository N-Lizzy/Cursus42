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
        try:
            for arg in args[1:]:
                scores.append(int(arg))
        except ValueError:
            print("Error: Argument is not a number")

        total_players = len(scores)
        total_scores = sum(scores)
        average_scores = total_scores / total_players
        high_score = max(scores)
        low_score = min(scores)
        Score_range = high_score - low_score

        print(f"Total players: {total_players}")
        print(f"Total score: {total_scores}")
        print(f"Average score: {average_scores}")
        print(f"High score: {high_score}")
        print(f"Low score: {low_score}")
        print(f"Score range: {Score_range}")

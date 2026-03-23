import typing
import random

name: str
action: str


def gen_event() -> typing.Generator[tuple[str, str], None, None]:
    players: list[str] = ["alice", "bob", "charlie", "dylan"]
    actions: list[str] = ["run", "eat", "sleep", "grab", "move",
                          "climb", "swim", "release", "use"]

    while True:
        name = random.choice(players)
        action = random.choice(actions)
        yield (name, action)


def consume_event(events: list[tuple[str, str]]
                  ) -> typing.Generator[tuple[str, str], None, None]:
    while len(events) > 0:
        index: int = random.randrange(len(events))
        event: tuple[str, str] = events.pop(index)
        yield event


if __name__ == "__main__":
    print("=== Game Data Stream Processor ===")

    stream = gen_event()

    for i in range(1000):
        name, action = next(stream)
        print(f"Event {i}: Player {name} did action {action}")

    event_list: list[tuple[str, str]] = [next(stream) for x in range(10)]
    print(f"Built list of 10 events: {event_list}")

    for event in consume_event(event_list):
        print(f"Got event from list: {event}")
        print(f"Remains in list: {event_list}")

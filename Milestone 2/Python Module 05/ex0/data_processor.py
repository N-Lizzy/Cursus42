from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._data: list[str] = list()
        self._rank: int = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        if len(self._data) == 0:
            raise IndexError("No data available in processor")
        oldest_data: str = self._data.pop(0)
        current_rank: int = self._rank
        self._rank = self._rank + 1
        return (current_rank, oldest_data)


class NumericProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if type(data) is int or type(data) is float:
            return True
        if type(data) is list:
            for element in data:
                if type(element) is not int and type(element) is not float:
                    return False
            return True
        return False

    def ingest(self, data: int | float | list[int | float]) -> None:
        is_valid: bool = self.validate(data)
        if is_valid is False:
            raise ValueError("Improper numeric data")

        if type(data) is list:
            number_list: list[int | float] = data
            for number in number_list:
                number_as_string: str = str(number)
                self._data.append(number_as_string)
        else:
            single_number: int | float = data
            number_as_string: str = str(single_number)
            self._data.append(number_as_string)


class TextProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if type(data) is str:
            return True
        if type(data) is list:
            for element in data:
                if type(element) is not str:
                    return False
            return True
        return False

    def ingest(self, data: str | list[str]) -> None:
        is_valid: bool = self.validate(data)
        if is_valid is False:
            raise ValueError("Improper text data")

        if type(data) is list:
            text_list: list[str] = data
            for text in text_list:
                self._data.append(text)
        else:
            single_text: str = data
            self._data.append(single_text)


class LogProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        def is_valid_log_entry(entry: Any) -> bool:
            if type(entry) is not dict:
                return False
            entry_dict: dict[Any, Any] = entry
            for key in entry_dict:
                value = entry_dict[key]
                if type(key) is not str or type(value) is not str:
                    return False
            return True

        if type(data) is dict:
            return is_valid_log_entry(data)
        if type(data) is list:
            for element in data:
                if is_valid_log_entry(element) is False:
                    return False
            return True
        return False

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        is_valid: bool = self.validate(data)
        if is_valid is False:
            raise ValueError("Improper log data")

        def format_log_entry(entry: dict[str, str]) -> str:
            if "log_level" in entry and "log_message" in entry:
                level: str = entry["log_level"]
                message: str = entry["log_message"]
                return level + ": " + message

            result: str = ""
            first: bool = True
            for key in entry:
                value: str = entry[key]
                if first is True:
                    result = key + ": " + value
                    first = False
                else:
                    result = result + ", " + key + ": " + value
            return result

        if type(data) is list:
            log_list: list[dict[str, str]] = data
            for log in log_list:
                formatted_log: str = format_log_entry(log)
                self._data.append(formatted_log)
        else:
            single_log: dict[str, str] = data
            formatted_log: str = format_log_entry(single_log)
            self._data.append(formatted_log)


if __name__ == "__main__":
    print("=== Code Nexus - Data Processor ===")
    print("")

    print("Testing Numeric Processor...")
    numeric_processor: NumericProcessor = NumericProcessor()

    test_number: int = 42
    validation_result: bool = numeric_processor.validate(test_number)
    print(f"Trying to validate input '{test_number}': {validation_result}")

    test_string: str = "Hello"
    validation_result = numeric_processor.validate(test_string)
    print(f"Trying to validate input '{test_string}': {validation_result}")

    print("Test invalid ingestion of string 'foo' without prior validation:")
    try:
        numeric_processor.ingest("foo")  # type: ignore
    except ValueError as error:
        print(f"Got exception: {error}")

    numeric_data: list[int | float] = [1, 2, 3, 4, 5]
    print(f"Processing data: {numeric_data}")
    numeric_processor.ingest(numeric_data)

    print("Extracting 3 values...")
    for i in range(3):
        rank: int
        value: str
        rank, value = numeric_processor.output()
        print(f"Numeric value {rank}: {value}")

    print("\nTesting Text Processor...")
    text_processor: TextProcessor = TextProcessor()

    validation_number_in_text: bool = text_processor.validate(42)
    print(f"Trying to validate input '42': {validation_number_in_text}")

    text_data: list[str] = ["Hello", "Nexus", "World"]
    print(f"Processing data: {text_data}")
    text_processor.ingest(text_data)

    print("Extracting 1 value...")
    text_rank: int
    text_value: str
    text_rank, text_value = text_processor.output()
    print(f"Text value {text_rank}: {text_value}\n")

    print("Testing Log Processor...")
    log_processor: LogProcessor = LogProcessor()

    validation_string_in_log: bool = log_processor.validate("Hello")
    print(f"Trying to validate input 'Hello': {validation_string_in_log}")

    log_data: list[dict[str, str]] = [
        {"log_level": "NOTICE", "log_message": "Connection to server"},
        {"log_level": "ERROR", "log_message": "Unauthorized access!!"}
    ]
    print(f"Processing data: {log_data}")
    log_processor.ingest(log_data)

    print("Extracting 2 values...")
    for i in range(2):
        log_rank: int
        log_value: str
        log_rank, log_value = log_processor.output()
        print(f"Log entry {log_rank}: {log_value}")
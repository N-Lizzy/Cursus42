from abc import ABC, abstractmethod
from typing import Any, Protocol


class ExportPlugin(Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...


class CSVExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        values: list[str] = [item[1] for item in data]
        line: str = ""
        first: bool = True

        for value in values:
            if first is True:
                line = value
                first = False
            else:
                line = line + "," + value

        print(f"CSV Output:\n{line}")


class JSONExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        json_str: str = "{"
        first: bool = True

        for rank, value in data:
            key: str = f"item_{rank}"
            pair: str = '"' + key + '": "' + value + '"'
            if first is True:
                json_str = json_str + pair
                first = False
            else:
                json_str = json_str + ", " + pair

        json_str = json_str + "}"
        print(f"JSON Output:\n{json_str}")


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._data: list[str] = list()
        self._rank: int = 0
        self._total_processed: int = 0

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

    def get_stats(self) -> tuple[int, int]:
        remaining: int = len(self._data)
        return (self._total_processed, remaining)

    def _add_to_storage(self, items: list[str]) -> None:
        for item in items:
            self._data.append(item)
            self._total_processed = self._total_processed + 1


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
        items_to_store: list[str] = list()
        if type(data) is list:
            number_list: list[int | float] = data
            for number in number_list:
                items_to_store.append(str(number))
        else:
            single_number: int | float = data
            items_to_store.append(str(single_number))
        self._add_to_storage(items_to_store)


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
        items_to_store: list[str] = list()
        if type(data) is list:
            text_list: list[str] = data
            for text in text_list:
                items_to_store.append(text)
        else:
            single_text: str = data
            items_to_store.append(single_text)
        self._add_to_storage(items_to_store)


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
                part: str = key + ": " + value
                if first is True:
                    result = part
                    first = False
                else:
                    result = result + ", " + part
            return result

        items_to_store: list[str] = list()
        if type(data) is list:
            log_list: list[dict[str, str]] = data
            for log in log_list:
                items_to_store.append(format_log_entry(log))
        else:
            single_log: dict[str, str] = data
            items_to_store.append(format_log_entry(single_log))
        self._add_to_storage(items_to_store)


class DataStream:
    def __init__(self) -> None:
        self._processors: list[DataProcessor] = list()

    def register_processor(self, proc: DataProcessor) -> None:
        self._processors.append(proc)

    def process_stream(self, stream: list[Any]) -> None:
        for element in stream:
            found_processor: bool = False
            for processor in self._processors:
                if processor.validate(element) is True:
                    try:
                        processor.ingest(element)  # type: ignore
                        found_processor = True
                        break
                    except ValueError:
                        continue
            if found_processor is False:
                print(f"DataStream error - Can't process "
                      f"element in stream: {element}")

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for processor in self._processors:
            data_to_export: list[tuple[int, str]] = list()
            for _ in range(nb):
                try:
                    rank: int
                    value: str
                    rank, value = processor.output()
                    data_to_export.append((rank, value))
                except IndexError:
                    break
            if len(data_to_export) > 0:
                plugin.process_output(data_to_export)

    def print_processors_stats(self) -> None:
        print("\n== DataStream statistics ==")
        if len(self._processors) == 0:
            print("No processor found, no data\n")
            return
        for processor in self._processors:
            processor_type: str = type(processor).__name__
            total: int
            remaining: int
            total, remaining = processor.get_stats()
            short_name: str = processor_type.replace("Processor", "")
            print(f"{short_name} Processor: total {total} items processed,"
                  f" remaining {remaining} on processor")
        print("")


if __name__ == "__main__":
    print("=== Code Nexus - Data Pipeline ===\n")
    print("Initialize Data Stream...\n")

    stream: DataStream = DataStream()
    stream.print_processors_stats()

    print("Registering Processors\n")
    numeric_proc: NumericProcessor = NumericProcessor()
    text_proc: TextProcessor = TextProcessor()
    log_proc: LogProcessor = LogProcessor()
    stream.register_processor(numeric_proc)
    stream.register_processor(text_proc)
    stream.register_processor(log_proc)

    first_batch: list[Any] = [
        "Hello world",
        [3.14, -1, 2.71],
        [{"log_level": "WARNING", "log_message":
          "Telnet access! Use ssh instead"},
         {"log_level": "INFO", "log_message": "User wil is connected"}],
        42,
        ["Hi", "five"]
    ]
    print(f"Send first batch of data on stream: {first_batch}")
    stream.process_stream(first_batch)
    stream.print_processors_stats()

    print("Send 3 processed data from each processor to a CSV plugin:")
    csv_plugin: CSVExportPlugin = CSVExportPlugin()
    stream.output_pipeline(3, csv_plugin)
    print("")
    stream.print_processors_stats()

    second_batch: list[Any] = [
        21,
        ["I love AI", "LLMs are wonderful", "Stay healthy"],
        [{"log_level": "ERROR", "log_message": "500 server crash"},
         {"log_level": "NOTICE", "log_message":
          "Certificate expires in 10 days"}],
        [32, 42, 64, 84, 128, 168],
        "World hello"
    ]
    print(f"Send another batch of data: {second_batch}")
    stream.process_stream(second_batch)
    stream.print_processors_stats()
    print("")

    print("Send 5 processed data from each processor to a JSON plugin:")
    json_plugin: JSONExportPlugin = JSONExportPlugin()
    stream.output_pipeline(5, json_plugin)
    stream.print_processors_stats()

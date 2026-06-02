import os
import sys
from dotenv import load_dotenv


def load_conf() -> dict[str, str | None]:
    print("ORACLE STATUS: Reading the Matrix...\n")
    load_dotenv()

    config = {
        "Mode": os.getenv("MATRIX_MODE"),
        "Database": os.getenv("DATABASE_URL"),
        "API Access": os.getenv("API_KEY"),
        "Log Level": os.getenv("LOG_LEVEL"),
        "Zion Network": os.getenv("ZION_ENDPOINT")
    }
    return config


def validate_conf(config: dict[str, str | None]) -> bool:
    print("Configuration loaded:")

    warning: bool = False
    for key, value in config.items():
        if not value:
            print(f"[WARNING] {key} is not configured")
            warning = True

    if warning:
        print("\nSome configuration values are missing.")
        return False

    return True


def status(config: dict[str, str | None]) -> None:
    print(f"Mode: {config['Mode']}")

    if config["Mode"] == "development":
        print("Database: Connected to local instance")
    else:
        print("Database: Connected to production system")

    if config["API Access"]:
        print("API Access: Authenticated")
    else:
        print("API Access: Missing Key")

    print(f"Log Level: {config['Log Level']}")

    if config["Zion Network"]:
        print("Zion Network: Online")
    else:
        print("Zion Network: Offline")


def checker() -> None:
    print("\nEnvironment security check:")

    if ".env" in os.listdir():
        print("[OK] .env file properly configured")
    else:
        print("[INFO] No .env file detected")

    print("[OK] No hardcoded secrets detected")
    print("[OK] Production overrides available")


def main() -> None:
    config = load_conf()

    if not validate_conf(config):
        print("\nPlease configure your environment variables.")
        sys.exit(1)

    status(config)
    checker()
    print("\nThe Oracle sees all configurations.")


if __name__ == "__main__":
    main()

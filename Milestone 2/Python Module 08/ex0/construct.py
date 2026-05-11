import os
import sys


def detect_virtual_environment():
    venv_path = os.environ.get("VIRTUAL_ENV")

    if venv_path:
        return True, venv_path
    return False, None


if __name__ == "__main__":
    is_in_venv, venv_path = detect_virtual_environment()
    print()

    if is_in_venv:
        print("MATRIX STATUS: Welcome to the construct")
        print(f"Current Python: {sys.executable}")
        print(f"Virtual Environment: {venv_path}\n")

        print("SUCCESS: You're in an isolated environment!")
        print("Safe to install packages without affecting")
        print("the global system.")
    else:
        print("MATRIX STATUS: You're still plugged in")
        print(f"Current Python: {sys.executable}")
        print("Virtual Environment: None detected\n")

        print("WARNING: You're in the global environment!")
        print("The machines can see everything you install.\n")

        print("To enter the construct, run:")
        print("  python -m venv matrix_env")
        print("  source matrix_env/bin/activate  # On Unix")
        print("  matrix_env\\Scripts\\activate  # On Windows\n")

        print("Then run this program again.\n")

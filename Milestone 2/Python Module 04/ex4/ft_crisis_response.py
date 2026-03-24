def read_archive(archive: str) -> None:
    print(f"CRISIS ALERT: Attempting access to '{archive}'...")
    try:
        with open(archive, "r") as read_file:
            data = read_file.read()
            print(f"SUCCESS: Archive recovered - ``{data}''")
            print("STATUS: Normal operations resumed\n")
    except FileNotFoundError:
        print("RESPONSE: Archive not found in storage matrix")
        print("STATUS: Crisis handled, system stable\n")
    except PermissionError:
        print("RESPONSE: Security protocols deny access")
        print("STATUS: Crisis handled, security maintained\n")
    except Exception as e:
        print(f"RESPONSE: Unexpected system anomaly: {e}")
        print("STATUS: Crisis contained\n")


if __name__ == "__main__":
    print("=== CYBER ARCHIVES - CRISIS RESPONSE SYSTEM ===\n")

    read_archive("lost_archive.txt")
    read_archive("classified_vault.txt")
    read_archive("standard_archive.txt")

    print("All crisis scenarios handled successfully. Archives secure.")

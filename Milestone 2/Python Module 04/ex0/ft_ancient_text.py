if __name__ == "__main__":
    print("=== CYBER ARCHIVES - DATA RECOVERY SYSTEM ===\n")
    print("Accessing Storage Vault: ancient_fragment.txt")

    try:
        f = open("ancient_fragment.txt", "r")
        print("Connection established...\n")

        print("RECOVERED DATA:")
        data: str = f.read()
        print(data)

        f.close()

        print("\nData recovery complete. Storage unit disconnected.")
    except FileNotFoundError:
        print("ERROR: Storage vault not found. Run data generator first.")

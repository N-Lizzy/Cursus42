import sys

if __name__ == "__main__":
    print("=== CYBER ARCHIVES - COMMUNICATION SYSTEM ===\n")

    id_input = input("Input Stream active. Enter archivist ID: ")
    status_input = input("Input Stream active. Enter status report: ")

    sys.stdout.write(f"\n[STANDARD] Archive status from "
                     f"{id_input}: {status_input}")
    sys.stderr.write("\n[ALERT] System diagnostic: "
                     "Communication channels verified\n")
    sys.stdout.write("[STANDARD] Data transmission complete\n")

    print("\nThree-channel communication test successful.")

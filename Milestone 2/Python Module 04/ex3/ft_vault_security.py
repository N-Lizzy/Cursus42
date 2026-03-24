if __name__ == "__main__":
    print("=== CYBER ARCHIVES - VAULT SECURITY SYSTEM ===\n")
    print("Initiating secure vault access...")

    with open("classified_data.txt", "r") as f:
        print("Vault connection established with failsafe protocols\n")

        print("SECURE EXTRACTION:")
        data: str = f.read()
        print(data)

    print("\nSECURE PRESERVATION:")
    with open("security_protocols.txt", "w") as f:
        protocol: str = "[CLASSIFIED] New security protocols archived"
        f.write(protocol)
        print(protocol)

    print("Vault automatically sealed upon completion\n")
    print("All vault operations completed with maximum security.")

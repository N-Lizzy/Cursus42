import sys
import importlib.util
from typing import Optional


def check_package(name: str) -> Optional[str]:
    spec = importlib.util.find_spec(name)
    if spec is None:
        return None
    try:
        mod = importlib.import_module(name)
        version = getattr(mod, "__version__", "unknown")
        return str(version)
    except Exception:
        return None


def show_dependency_manager_info() -> None:
    print("\nDependency manager comparison:")
    print("  pip:")
    print("    - Uses requirements.txt to list packages")
    print("    - Install with: pip install -r requirements.txt")
    print("    - Does NOT lock transitive dependency versions by default")
    print("  Poetry:")
    print("    - Uses pyproject.toml to declare dependencies")
    print("    - Generates poetry.lock for fully reproducible installs")
    print("    - Install with: poetry install")
    print("    - Manages virtual environments automatically")


def check_all_dependencies() -> bool:
    required = {
        "pandas": "Data manipulation ready",
        "numpy": "Numerical computation ready",
        "matplotlib": "Visualization ready",
    }
    all_ok = True
    print("Checking dependencies:")
    for pkg, description in required.items():
        version = check_package(pkg)
        if version:
            print(f"[OK] {pkg} ({version}) - {description}")
        else:
            print(f"[MISSING] {pkg} - {description}")
            all_ok = False

    if not all_ok:
        print("\nSome dependencies are missing. Install them with:")
        print("  pip:    pip install -r requirements.txt")
        print("  Poetry: poetry install")
    return all_ok


def run_analysis() -> None:
    import numpy as np
    import pandas as pd
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    print()
    print("Analyzing Matrix data...")
    n_points = 1000
    print(f"Processing {n_points} data points...")

    rng = np.random.default_rng(seed=42)
    time_steps = np.arange(n_points)
    signal = rng.normal(loc=0.0, scale=1.0, size=n_points)
    noise = rng.uniform(low=-0.5, high=0.5, size=n_points)
    matrix_data = signal + noise

    df = pd.DataFrame({
        "time": time_steps,
        "matrix_signal": matrix_data,
    })

    print("Generating visualization...")
    plt.plot(
        df["time"],
        df["matrix_signal"],
        color="pink",
        linewidth=1,
        linestyle="-",
        alpha=0.7)
    plt.title("Matrix Data")
    plt.xlabel("Time step")
    plt.ylabel("Signal amplitude")

    output_file = "matrix_analysis.png"
    plt.savefig(output_file, dpi=100)
    plt.close()

    print()
    print("Analysis complete!")
    print(f"Results saved to: {output_file}")


def main() -> None:
    print("LOADING STATUS: Loading programs...\n")

    all_ok = check_all_dependencies()
    show_dependency_manager_info()

    if not all_ok:
        sys.exit(1)

    run_analysis()


if __name__ == "__main__":
    main()

import subprocess
import os

def main():
    # Step 1: Clone vcpkg repository
    clone_cmd = ["git", "clone", "https://github.com/Microsoft/vcpkg.git"]
    subprocess.run(clone_cmd, check=True)

    # Change to vcpkg directory
    os.chdir("vcpkg")

    # Step 2: Bootstrap vcpkg
    bootstrap_cmd = ["./bootstrap-vcpkg.sh"]
    subprocess.run(bootstrap_cmd, check=True)

    # Step 3: Install vcpkg
    install_cmd = ["./vcpkg", "install"]
    subprocess.run(install_cmd, check=True)

if __name__ == "__main__":
    main()

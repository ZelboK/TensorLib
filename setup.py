import subprocess
import os
import platform

def get_os():
    return platform.system()

def run_bootstrap(bootstrap_cmd):
    subprocess.run(bootstrap_cmd, check=True)


def main():
    # Step 1: Clone vcpkg repository
    clone_cmd = ["git", "clone", "https://github.com/Microsoft/vcpkg.git"]
    subprocess.run(clone_cmd, check=True)

    # Change to vcpkg directory
    os.chdir("vcpkg")

    # Step 2: Bootstrap vcpkg
    match get_os():
        case "Windows":
            run_bootstrap(["./bootstrap-vcpkg.bat"])
        case _:
            run_bootstrap(["./bootstrap-vcpkg.sh"])
    # Step 3: Install vcpkg
    install_cmd = ["./vcpkg", "install"]
    subprocess.run(install_cmd, check=True)

if __name__ == "__main__":
    main()

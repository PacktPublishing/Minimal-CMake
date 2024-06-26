import subprocess
import time
import os
import signal
import sys

def main():
    # Launch the application
    try:
        app_process = subprocess.Popen(["../install/bin/minimal-cmake_game-of-life_window"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except Exception as e:
        print(f"Failed to launch application: {e}", file=sys.stderr)
        return 1
    
    # Wait for a short duration to simulate some runtime
    time.sleep(5)
    
    # Terminate the application
    try:
        if os.name == 'nt':
            # Windows
            app_process.terminate()
            app_process.wait(timeout=5)
        else:
            # Unix-like systems
            app_process.send_signal(signal.SIGTERM)
            app_process.wait(timeout=5)
    except Exception as e:
        print(f"Failed to terminate application: {e}", file=sys.stderr)
        return 1
    
    # Check the return code of the application
    if app_process.returncode == 0:
        print("Application terminated successfully.")
        return 0
    else:
        print("Application termination failed.", file=sys.stderr)
        print(app_process.stderr.read().decode(), file=sys.stderr)
        return 1

if __name__ == "__main__":
    sys.exit(main())

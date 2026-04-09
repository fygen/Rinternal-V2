import pytest
import requests
import json
import time

# --- CONFIGURATION ---
DEVICE_IP = "10.0.0.72"
BASE_URL = f"http://{DEVICE_IP}"

def get_commands():
    """Fetches the list of commands from the device."""
    url = f"{BASE_URL}/execute?val=HELPER getCommandsJSON"
    try:
        response = requests.get(url, timeout=10)
        response.raise_for_status()
        return json.loads(response.text)
    except (requests.exceptions.RequestException, json.JSONDecodeError) as e:
        pytest.fail(f"Failed to fetch commands: {e}")

def get_dummy_value(param_type):
    """Returns a dummy value for a given parameter type."""
    pt = param_type.lower()
    if "string" in pt or "char" in pt:
        return "test"
    elif any(x in pt for x in ["int", "long", "short"]):
        return "123"
    elif any(x in pt for x in ["float", "double"]):
        return "1.23"
    elif "bool" in pt:
        return "true"
    else:
        return "unknown"

# Fetch commands once and use for all tests
commands = get_commands()

# Filter out commands that should not be tested automatically
def filter_commands(command):
    module = command['module']
    name = command['name']
    
    # Skip disruptive or problematic commands
    if module == "WIFI" and name in ["connect", "reset", "restart"]:
        return False
    if module == "HELPER" and name == "wtf":
        return False
        
    # Skip commands with unknown parameter types
    params = command['params']
    param_values = [get_dummy_value(p) for p in params]
    if "unknown" in param_values:
        return False
        
    return True

runnable_commands = [cmd for cmd in commands if filter_commands(cmd)]

@pytest.mark.parametrize("command", runnable_commands)
def test_command(command):
    """
    This is a parameterized test that runs for each command.
    To add a new test for a command, you can either add a new dictionary
    to the `runnable_commands` list, or create a new test function.
    
    To add a new test function for a specific command, you can do this:
    
    def test_my_specific_command():
        # Your test logic here
        pass
    """
    module = command['module']
    name = command['name']
    params = command['params']
    
    param_values = [get_dummy_value(p) for p in params]
    val_str = f"{module} {name} {' '.join(param_values)}"
    url = f"{BASE_URL}/execute?val={val_str}"
    
    print(f"Testing: {val_str}")
    
    retries = 1
    for i in range(retries + 1):
        try:
            response = requests.get(url, timeout=20)
            response.raise_for_status()
            print(f"  -> Status: {response.status_code}, Response: {response.text[:80]}...")
            assert response.status_code == 200
            return # Success
        except requests.exceptions.ConnectionError as e:
            if i < retries:
                print(f"  -> Connection error: {e}. Retrying in 5s...")
                time.sleep(5)
            else:
                pytest.fail(f"'{val_str}' failed after {retries} retries: {e}")
        except requests.exceptions.RequestException as e:
            pytest.fail(f"'{val_str}' failed with error: {e}")

if __name__ == "__main__":
    pytest.main()

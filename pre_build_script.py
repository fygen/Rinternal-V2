Import("env")

def run_generate_shell(source, target, item):
    print("Running Auto-Shell Generation...")
    import subprocess
    # Run your scripts here
    subprocess.run(["python", "tag_headers.py"])
    subprocess.run(["python", "generate_dispatcher.py"])

# Execute before compiling
env.AddPreAction("buildprog", run_generate_shell)
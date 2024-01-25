import subprocess
import os
    
def run_cpp_file():
    # Compile the C++ code
    cpp_filename = 'smart_test.cpp'
    compile_process = subprocess.run(["g++", cpp_filename, "-o", "temp_executable"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    # Check for compilation errors
    if compile_process.returncode != 0:
        print("Compilation error:")
        print(compile_process.stderr)
        return

    # Run the compiled executable
    run_process = subprocess.run(["./temp_executable"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    valgrind_cmd = ["valgrind", "--leak-check=full", "./temp_executable"]

    try:
        process = subprocess.Popen(valgrind_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        
        if "ERROR SUMMARY: 0 errors" not in stderr.decode():
            print("Valgrind detected memory leaks. Fix the memory errors!")
        else:
            print("No memory leaks detected. You have passed this PA!")
    except subprocess.CalledProcessError as e:
        print("Valgrind error")
    
    try:
        os.remove("./temp_executable")
    except FileNotFoundError:
        print("Compilation error")


run_cpp_file()

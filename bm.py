import os
import subprocess
import sys
import shutil
import json

EXE_OUTPUT_FOLDER_NAME = './exe/'
OBJ_OUTPUT_FOLDER_NAME = './obj/'

FREEGLUT_INCLUDE_PATH = os.path.abspath('./freeglut/include')
FREEGLUT_LIB_PATH = os.path.abspath('./freeglut/lib/x64')

DEPS = json.load(open('deps.json'))

def compile_to_object(file_path):
    if not os.path.isfile(file_path):
        print(f"File {file_path} does not exist.")
        return

    base_name = os.path.basename(file_path)
    file_name, _ext = os.path.splitext(base_name)

    if not os.path.exists(OBJ_OUTPUT_FOLDER_NAME):
        os.mkdir(OBJ_OUTPUT_FOLDER_NAME)

    output_file = OBJ_OUTPUT_FOLDER_NAME + file_name + '.o'

    objs = [output_file]
    deps = DEPS[file_name]

    includes_freeglut = False
    for dep in deps:
        if 'GL/freeglut' in dep:
            includes_freeglut = True
            continue
        if 'GL/gl' in dep:
            continue
        if dep == file_name: continue
        deps_objs, deps_deps = compile_to_object(f'./src/{dep}.cpp')
        objs += deps_objs
        deps += deps_deps

    # Compile the code
    compile_command = [
        'g++', file_path, '-c', '-o', output_file
    ]

    if includes_freeglut:
        compile_command += [
            '-I', FREEGLUT_INCLUDE_PATH
        ]

    compile_process = subprocess.run(compile_command, capture_output=True, text=True)

    if compile_process.returncode != 0:
        print("Compilation failed:")
        print(compile_process.stderr)
        return

    print("Compilation successful.")
    return list(set(objs)), list(set(deps))

def compile(file_path):
    base_name = os.path.basename(file_path)
    file_name, _ext = os.path.splitext(base_name)

    if not os.path.exists(EXE_OUTPUT_FOLDER_NAME):
        os.mkdir(EXE_OUTPUT_FOLDER_NAME)

    objs, deps = compile_to_object(file_path)

    output_file = EXE_OUTPUT_FOLDER_NAME + file_name + '.exe'

    # Compile the code
    compile_command = ['g++'] + objs + ['-o', output_file]

    includes_freeglut = any('GL/freeglut' in dep for dep in deps)
    includes_gl = any('GL/gl' in dep for dep in deps)

    if includes_freeglut:
        compile_command += [
            '-L', FREEGLUT_LIB_PATH,
            '-lfreeglut', '-lopengl32'
        ]

    if includes_gl:
        compile_command += ['-lglu32']

    compile_process = subprocess.run(compile_command, capture_output=True, text=True)

    if compile_process.returncode != 0:
        print("Compilation failed:")
        print(compile_process.stderr)
        return

    print("Compilation successful.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        usage_message = """
        Usage:
            - compile: python bm.py <source_file>
            - clear:   python bm.py clear
        """
        print("Usage: python bm.py <source_file>|clear")
    else:
        arg = sys.argv[1]
        if arg == 'clear':
            shutil.rmtree(OBJ_OUTPUT_FOLDER_NAME, ignore_errors=True)
            shutil.rmtree(EXE_OUTPUT_FOLDER_NAME, ignore_errors=True)
        else:
            compile(f'./src/{sys.argv[1]}.cpp')

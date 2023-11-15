import platform
import re
import os
import fnmatch

def navigate_all_files(root_path, patterns):
    """
    Iterates all files that matches the given patterns and return a Yield.
    Args:
        root_path (_type_): _description_
        patterns (_type_): _description_
    """
    for root, dirs, files in os.walk("manual_tests_output"):
        for pattern in patterns:
            for filename in fnmatch.filter(files, pattern):
                yield os.path.join(root, filename)

def get_all_files(root_path, pattern):
    """
    Returns a list of all files that matches the given patterns from the root path
    Such as : manual_tests_output/PhysicsAnimation/SimpleMassSpringAnimation/data.#line2,0281,y.npy
    Args:
        root_path (_type_): _description_
        pattern (_type_): _description_
    """
    ret = []
    for filepath in navigate_all_files(root_path, pattern):
        ret.append(filepath)
    return ret
    
if __name__ == "__main__":
    get_all_files("manual_tests_output",["*" + ".npy"])

    
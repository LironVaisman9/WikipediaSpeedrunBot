import os

FILE_NAME = ""

def read_result_file() -> str:
    file_path = os.path.join(os.path.dirname(__file__), "..", FILE_NAME)
    with open(file_path, "r") as file:
        content = file.read()
        return content
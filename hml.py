import os

file_count: int = 0


def count_lines_in_file(file_path):
    """Counts the number of non-empty lines in a file."""
    with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()
        # Filter out empty lines and lines with only spaces
        return sum(1 for line in lines if line.strip())


def scan_folder_for_code_lines(folder_path):
    total_lines = 0
    file_types = (".hpp", ".ino", ".cpp")  # Files to search for
    global file_count
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file.endswith(file_types):
                file_count += 1
                file_path = os.path.join(root, file)
                lines_in_file = count_lines_in_file(file_path)
                total_lines += lines_in_file
                print(f"File: {file_path} - {lines_in_file} lines")
    return total_lines


if __name__ == "__main__":
    folder_path = "./"
    total_lines = scan_folder_for_code_lines(folder_path)
    print(f"Total lines of code in .py and .conf files: {total_lines}")
    print(f"Total file count: {file_count}")

import re  # Import regex module

"""
EECS 348 Assignment 3 - Regex File Searcher
Author: Alice J Mungamuri
Student ID: XXXXXX
Date: February 27, 2025

Description:
This program reads a user-specified file and searches for occurrences of a user-specified regex pattern.
It prints all matches found on each line or "no match found" if none exist.

Inputs:
- A filename provided by the user.
- A regex pattern entered in the format /pattern/.

Outputs:
- Prints each line number and all matches found in that line.
- Prints "no match found" for lines without matches.

Sources:
- Python documentation for regex (`re` module)
- Stack Overflow for regex validation examples
- ChatGPT for regex logic refinement
"""

# Step 1: Get the filename from the user
filename = input("Enter the filename: ")

try:
    # Try opening the file
    with open(filename, "r") as file:
        lines = file.readlines()  # Read all lines from the file
except FileNotFoundError:
    print("Unable to open file.")
    exit()  # Exit the program if the file cannot be opened

# Step 2: Get the regex pattern from the user
regex_input = input("Enter a regex pattern in the format /pattern/: ")

# Ensure the regex is correctly formatted with slashes
if not (regex_input.startswith("/") and regex_input.endswith("/")):
    print("Invalid regex pattern.")
    exit()

# Extract the actual regex pattern by removing the surrounding slashes
regex_pattern = regex_input[1:-1]

# Step 3: Validate the regex pattern
try:
    compiled_regex = re.compile(regex_pattern)  # Compile the regex pattern
except re.error:
    print("Invalid regex pattern.")
    exit()

# Function to find all matches in a given line
def find_matches(line, regex):
    """
    Searches for all occurrences of the regex pattern in the given line.
    :param line: A single line of text.
    :param regex: The compiled regex pattern.
    :return: A list of matches or ["no match found"] if none exist.
    """
    matches = regex.findall(line)  # Find all matches in the line
    if matches:
        return matches  # Return the list of matches
    else:
        return ["no match found"]  # Return "no match found" if no match exists

# Step 4: Process the file line by line
for i, line in enumerate(lines):
    line = line.strip()  # Remove leading/trailing spaces and newlines
    
    if not line:  # Skip empty lines
        continue

    matches = find_matches(line, compiled_regex)  # Find matches in the current line

    print(f"Line {i+1}: {' | '.join(matches)}")  # Print all matches, separated by '|'

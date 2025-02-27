import re  # Import regex module

"""
EECS 348 Assignment 3 
Author: Alice J Mungamuri
Student ID: 3117704
Date: February 27, 2025

Inputs:
filename
the regex pattern but user has to give it /..../

Outputs:
- Prints each line number and all matches found in that line.
otherwise No Match FOud

Sources:
- Stack Overflow how to validate
- ChatGPT for regex logic refinement
- TA
"""

# Step 1: Get the filename from the user
filename = input("Enter the filename: ")

try:
    # I just used the try except to try an open the filename given by input from the user  - error if invalud
    with open(filename, "r") as file:
        lines = file.readlines()  # Read all lines from the file
except FileNotFoundError:
    print("Cannot open file.")
    exit()  # Exit the program

# Get regex pattern from the user
regexUser = input("Enter a regex pattern in the format /pattern/: ")

# correctly inputted check
if not (regexUser.startswith("/") and regexUser.endswith("/")):
    print("Invalid regex pattern.")
    exit()

# Extract the actual regex pattern strip the first and last
regex_pattern = regexUser[1:-1]

# validationt
try:
    compiled_regex = re.compile(regex_pattern)  # Compile the regex pattern , this was helped by TA in class
except re.error:
    print("Invalid regex pattern.") # try except if its not valid as per assignment
    exit()

# Function to find all matches in a given line
def find_matches(line, regex):
    """
    Searches for all occurrences of the regex pattern in the given line.

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

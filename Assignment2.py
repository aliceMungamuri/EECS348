"""
EECS 348 Assignment 2 - Regular Expressions
Author: Alice J Mungamuri
Date Created: February 12, 2025
Description:
    This program reads a test file containing 33 strings and applies regex patterns 
    using the Python `re` library to find matches based on provided rules. 
    It prints the matched substring or "no match found" if no match is detected.
Inputs:
    - Assignment2_Test_File.txt (contains 33 strings, one per line)
Outputs:
    - Prints matched substrings or "no match found" for each line.
"""

import re

def process_line(line, pattern):
    """Applies a regex pattern to a line and returns the matched substring or 'no match found'."""
    match = re.search(pattern, line)
    return match.group() if match else "no match found"

def main():
    """Reads the test file and applies regex patterns to each line."""
    try:
        with open("Assignment2_Test_File.txt", "r") as file:
            lines = file.readlines()
        
        patterns = [
            r"^a.*",       # Matches strings that start with 'a'
            r".*b$",       # Matches strings that end with 'b'
            r"\d+",       # Matches one or more digits
            r"[A-Za-z]+",  # Matches only alphabetic characters
            r"^abra",      # Matches strings that start with 'abra'
            r"c.t",        # Matches 'cat', 'cut', etc. (any character between 'c' and 't')
        ]
        
        for i, line in enumerate(lines):
            line = line.strip()
            if not line:
                continue
            
            match_found = False
            for pattern in patterns:
                result = process_line(line, pattern)
                if result != "no match found":
                    print(f"Line {i+1}: {result}")
                    match_found = True
                    break  # Stop checking once a match is found
            
            if not match_found:
                print(f"Line {i+1}: no match found")
    
    except FileNotFoundError:
        print("Error: Assignment2_Test_File.txt not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()

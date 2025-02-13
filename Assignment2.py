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

def getLine(line, pattern):
    """Applies a regex pattern to a line and returns the matched substring or 'no match found'."""
    match = re.search(pattern, line)
    return match.group() if match else "no match found"

def main():
    """Reads the test file and applies regex patterns to each line."""
    try:
        with open("Assignment2_Test_File.txt", "r") as file: # this opens the file
            lines = file.readlines() # this reads the lines of the file one by one
        
        patterns = [ # this is for each of the patterns - I give the regular expressions 
            r"^a.*",       # this will match the strings that start with a
            r".*b$",       # this goes with the strings that end with b
            r"\d+",       # this matches with 1 or more digits
            r"[A-Za-z]+",  # this goes with alphabetic characters - capital and lowercase
            r"^abra",      # the strings that start with abra
            r"c.t",        # if theres a character between c and t itll match
        ]
        
        for i, line in enumerate(lines):
            line = line.strip()
            if not line:
                continue
            
            match_found = False
            for pattern in patterns:
                result = getLine(line, pattern)
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


main()

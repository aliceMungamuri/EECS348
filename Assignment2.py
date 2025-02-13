import re  # this imports the regex module from python for pattern matching

def getLine(line, regexPttrn):  # gets a string from the file and then the regex pattern
    """Applies a regex pattern to a line and returns the matched substring or 'no match found'."""
    posMatch = re.search(regexPttrn, line)  # this makes it look for a match
    if posMatch:  # if the match is found posMatch is valid and takes the substring that matched the regex pattern; otherwise it's nothing
        return posMatch.group()
    else:
        return "no match found"

def main():
    """Reads the test file and applies regex patterns to each line."""
    with open("Assignment2_Test_File.txt", "r") as file:  # this opens the file
        lines = file.readlines()  # this reads the lines of the file one by one
    
    patterns = [  # this is for each of the patterns - I give the regular expressions 
        r"^[aA].*",       # Ensures the entire string starts with 'a' or 'A'
        r".*b$",          # Matches strings that end with 'b'
        r"^\d+$",         # Matches only strings that are entirely digits
        r"^[A-Za-z]+$",   # Ensures the entire string contains only alphabetic characters
        r"^abra",         # Matches strings that start with 'abra'
        r"c.t",           # Matches strings where 'c' is followed by any character and then 't'
        r"^\w+$",         # Matches strings containing only alphanumeric characters (including underscores)
        r"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$",  # Matches email addresses
        r"^\d{3}-\d{3}-\d{4}$",  # Matches phone numbers in the format xxx-xxx-xxxx
    ]
    
    for i, line in enumerate(lines):  # keeps track by index (i) and lines
        line = line.strip()  # removes extra spaces or \n
        
        if not line:  # skipping empty lines
            continue
        
        match_found = False  # boolean on if the match is found or not
        
        for regexPttrn in patterns:  # loops through each regex pattern
            ans = getLine(line, regexPttrn)  # applies the pattern to the line and stores the result
            if ans != "no match found":  # if a match is found
                print(f"Line {i+1}: {ans}")
                match_found = True
                
            
        if not match_found:  # if no match was found after checking all patterns
            print(f"Line {i+1}: no match found")

main()
import re  # this imports the regex module from Python for pattern matching

def getLine(line, regexPttrn):  # gets a string from the file and then the regex pattern
    """Applies a regex pattern to a line and returns the matched substring or 'no match found'."""
    posMatch = re.search(regexPttrn, line)  # looks for the match in the line using the pattern
    if posMatch:  # if the match is found, posMatch is valid and takes the substring that matched the regex pattern
        return posMatch.group()
    else:
        return "no match found"  # if no match, return "no match found"

def main():
    """Reads the test file and applies regex patterns to each line."""
    with open("Assignment2_Test_File.txt", "r") as file:  # opens the test file
        lines = file.readlines()  # reads the lines of the file, one by one
    
    patterns = [  # list of regular expressions for pattern matching
        r"^ac",           # Matches any line starting with 'ac'
        r"^acd",          # Matches any line starting with 'acd'
        r"^acde",         # Matches any line starting with 'acde'
        r"^a$",           # Matches 'a' at the beginning and end of a line
        r"^nal",          # Matches any line starting with 'nal'
        r"^abc",          # Matches any line starting with 'abc'
        r"^ab",           # Matches any line starting with 'ab'
        r"^a$",           # Matches line ending with 'a'
        r"^.*a$",         # Matches lines that end with 'a'
        r"^main$",        # Matches the exact string 'main' at the start and end
        r"^woman$",       # Matches the exact string 'woman'
        r"^abracadabra$", # Matches the string 'abracadabra'
        r"[a-fxY8-9]",    # Matches any character in the range a-f, x, Y, or digits 8-9
        r"^My dog has fleas.$",  # Matches the exact string 'My dog has fleas.'
        r"^.*a$",         # Matches strings that end with 'a'
        r"^.*\d$",        # Matches strings that end with a digit
        r"^.*b$",         # Matches strings that end with 'b'
        r"\bDoge\b",      # Matches the exact word 'Doge' (with word boundaries)
        r"r.*b",          # Matches lines that contain 'r' followed by any characters and then 'b'
        r"\d",            # Matches any single digit
        r"\s",            # Matches any whitespace character
        r"ex?a",          # Matches 'ex' followed by zero or one 'a'
        r"\\we",          # Matches the literal string '\we'
    ]
    
    for i, line in enumerate(lines):  # keeps track by index (i) and lines
        line = line.strip()  # removes extra spaces or newlines
        
        if not line:  # skipping empty lines
            continue
        
        match_found = False  # boolean to track if a match is found
        
        for regexPttrn in patterns:  # loops through each regex pattern
            ans = getLine(line, regexPttrn)  # applies the pattern to the line and stores the result
            if ans != "no match found":  # if a match is found
                print(f"Line {i+1}: {ans}")
                match_found = True
                # Remove 'break' so it continues checking other patterns
            
        if not match_found:  # if no match was found after checking all patterns
            print(f"Line {i+1}: no match found")

main()

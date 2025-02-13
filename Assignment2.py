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
        r"ac",           # Matches line with ac in it
        r"b",           # Matches line with a b in it
        r"^acd",          # Matches any line starting with acd
        r"^acde",         # Matches any line starting with acde
        r"^a$",           # Matches 'a' at the beginning and end of a line
        r"^a",           # Matches line with a b in it
        r"^ab",           # Matches line starting with an ab in it
        r"ma+n",           # Matches line with a ma directly in front of an n
        r"..",           # idek is it matching any single character
        r"^abra", # Matches the stringabre at the beginning
        r"abra$", # Matches the stringabre at the end
        r"ca.", # gets the ca followed by a singular character
        r"r.*b", # gets the acadabra 
        r"cx?a", # gets the ca in abracadabra
        r"[a-fxY0-9]",    # a through f and XY and then 0-9
        r"[^a-fxY0-9]",    # a through f and XY and then 0-9 at the beginning
        r"flea|tick",    # gets flea
        r"(My|Your) (dog|cat)",    # gets flea
        r"\bDogg\b",      # Matches the exact word 'Doge' (with word boundaries)
        r"\d",      # gets first digit
        r"\s",      # gets first space
        r"\w+",      # gets first word


        
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

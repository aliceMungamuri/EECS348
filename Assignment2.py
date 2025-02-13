import re  # this imports the regex module from Python for pattern matching

def getLine(line, regexPttrn):  # gets a string from the file and then the regex pattern
    
    posMatch = re.search(regexPttrn, line)  # looks for the match in the line using the pattern
    if posMatch:  # if the match is found, posMatch is valid and takes the substring that matched the regex pattern
        return posMatch.group()
    else:
        return "no match found"  # if no match, return "no match found"

def main():
  
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
        r"\w+"      # gets first word


        
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

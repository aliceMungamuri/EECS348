# EECS 348 Assignment 1
# CEO EMAIL Prioritization Program
# Student ID = 3117704
# Author: Alice Mungamuri
# Creation Date: 1/ 30/2025
# Description: Inbow mail info
# Inputs: Reads  Assignment1_Test_File.txt. Output: next email and num unread

class EMAIL: # instantiates the class 
    def __init__(self, catSender, subject, date, order): # catSender = the category of the sender - these are all the parameters
        self.catSender = catSender  # all of these isassigning the variable to the self property of the object - is it necessary to comment it for each of the variables because its the same thing
        self.subject = subject # same thing as above 
        self.date = date# same thing as above 
        self.order = order# same thing as above 
        self.priority = self.getPriority()# this is to set it the the output bc we need to determine the priority after
    
    def getPriority(self): # function to assign  priority 0 just saying that Boss is first - otherperson is the lowest
        priority_map = {
            "Boss": 5, # these are all just the assigned values in order of importance
            "Subordinate": 4,
            "Peer": 3,
            "ImportantPerson": 2,
            "OtherPerson": 1
        }
        return (priority_map[self.catSender], self.date, -self.order)  # this whole thing is to push the most recent emails first - using the arrival order

    def __lt__(self, other): # using the magic methods less than operatos
        return self.priority < other.priority # compares those 2 objects in the  EMAIL class

    def __str__(self): # just an easier way to print with all those variables 
        return f"Sender: {self.catSender}\nSubject: {self.subject}\nDate: {self.date}" 

class MaxHeap:
    def __init__(self):
        self.heap = [] # this is where the list based implementation comes int ot play - will be added to this
    
    def push(self, email): # these functions are straighht from my 268 github - all very straight forwas
        self.heap.append(email) # adds to the heap
        self.upHeap(len(self.heap) - 1) # this ensures it is in the correct order so the max heap stays a max heap
    
    def pop(self): # removing from the heap - from 268 MaxHeap project - this method just removes/ returns the highest prioty email 
        if len(self.heap) > 1: # if theres mult emails
            self._swap(0, len(self.heap) - 1) # swaps the root to the last element - len - 1
            maxEm = self.heap.pop() 
            self.downHeap(0) # 
        elif self.heap: # if theres just one element
            maxEm = self.heap.pop() # removed
        else: # this is just in case its empty
            return None # itll return None 
        return maxEm # returning the max email
    
    def peek(self): # returns the root whhich is a lso the highest prioriyt - if its empty then None
        return self.heap[0] if self.heap else None # explained in the above
    
    def upHeap(self, index):  # upehap function
        biggest = (index - 1) // 2 # this gets the parent index of a given node
        while index > 0 and self.heap[index] > self.heap[parent]: # this will loop while the node isnt at the root and has a higher priorotu than the parent
            self._swap(index, biggest) # keeps the order in the heap swaps child w parent
            index = biggest # updates to move up the heap 
            biggest = (index - 1) // 2 # has ot redo the parent index for the next time
    
    def downHeap(self, index):
        smaller = 2 * index + 1 # this gets the left child index of the node
        while smaller < len(self.heap): # if at least one child itll look
            if smaller + 1 < len(self.heap) and self.heap[smaller + 1] > self.heap[smaller]: # if right has higher proority than ledt update child to be right
                smaller += 1
            if self.heap[index] > self.heap[smaller]: # this ends the loop cur nod is> the highest priority child
                break # ends loop
            self._swap(index, smaller) # swaps cur node and highest priority child
            index = smaller # updates index so it cont down heap
            smaller = 2 * index + 1 # you have to recalculate the left child for next time
    
    def _swap(self, i, j): # this is just to swap the elements at  iand j in heap
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i] # look at above
    
    def __len__(self):
        return len(self.heap) # len of list = num emails

def process_commands(filename): # this is the big one - it does all the coomands
    inbox = MaxHeap()
    order = 0 # makes the order counter 0
    
    with open(filename, 'r') as file: # this is just cookie cutter open file and go through each line and read - courtesy 268
        for line in file:
            parts = line.strip().split(',', 2) # splits into sender category subject and date
            command = parts[0].split()[0] # takes the command  type from the first part
            
            if command == "EMAIL": # means to process it as a new email
                catSender, subject, date = parts # takes the sender category subj and date
                catSender = catSender.split()[1]  # Extract actual category
                email = EMAIL(catSender, subject, date, order) # takes the actual category from the string
                inbox.push(email) # new email into the maxheap
                order += 1 # increment
            elif command == "NEXT": # display the highest priority emal
                next_email = inbox.peek() # looks at it
                print("Next email:") # just printing that to go with how the example gave the output
                print(next_email if next_email else "No emails ") # prints the detail but if nothing then says none
            elif command == "READ": # removes/display the hoghes priority email
                read_email = inbox.pop() # removes from heap
                if not read_email: # check if there was an email
                    print("No emails.")
            elif command == "COUNT": # shows the num of emails
                print(f"There are {len(inbox)} emails to read.") # shows the unread emails

def main (): # main funtion opens the text files and start the process 
    process_commands("Assignment1_Test_File.txt") # this is the text file name that was given

main()

# EECS 348 Assignment 1
# CEO Email Prioritization Program
# Author: Alice J Mungamuri
# Creation Date: January 30, 2025
# Description: This program implements a priority queue for email management using a MaxHeap.
# Inputs: Reads commands from 'Assignment1_Test_File.txt'.
# Outputs: Displays the next email and count of unread emails.

class Email:
    def __init__(self, sender_category, subject, date, arrival_order):
        self.sender_category = sender_category
        self.subject = subject
        self.date = date
        self.arrival_order = arrival_order
        self.priority = self.calculate_priority()
    
    def calculate_priority(self):
        priority_map = {
            "Boss": 5,
            "Subordinate": 4,
            "Peer": 3,
            "ImportantPerson": 2,
            "OtherPerson": 1
        }
        return (priority_map[self.sender_category], self.date, -self.arrival_order)  # Higher date, recent emails first

    def __lt__(self, other):
        return self.priority < other.priority

    def __str__(self):
        return f"Sender: {self.sender_category}\nSubject: {self.subject}\nDate: {self.date}"

class MaxHeap:
    def __init__(self):
        self.heap = []
    
    def push(self, email):
        self.heap.append(email)
        self._heapify_up(len(self.heap) - 1)
    
    def pop(self):
        if len(self.heap) > 1:
            self._swap(0, len(self.heap) - 1)
            max_email = self.heap.pop()
            self._heapify_down(0)
        elif self.heap:
            max_email = self.heap.pop()
        else:
            return None
        return max_email
    
    def peek(self):
        return self.heap[0] if self.heap else None
    
    def _heapify_up(self, index):
        parent = (index - 1) // 2
        while index > 0 and self.heap[index] > self.heap[parent]:
            self._swap(index, parent)
            index = parent
            parent = (index - 1) // 2
    
    def _heapify_down(self, index):
        child = 2 * index + 1
        while child < len(self.heap):
            if child + 1 < len(self.heap) and self.heap[child + 1] > self.heap[child]:
                child += 1
            if self.heap[index] > self.heap[child]:
                break
            self._swap(index, child)
            index = child
            child = 2 * index + 1
    
    def _swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]
    
    def __len__(self):
        return len(self.heap)

def process_commands(filename):
    inbox = MaxHeap()
    arrival_order = 0
    
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split(',', 2)
            command = parts[0].split()[0]
            
            if command == "EMAIL":
                sender_category, subject, date = parts
                sender_category = sender_category.split()[1]  # Extract actual category
                email = Email(sender_category, subject, date, arrival_order)
                inbox.push(email)
                arrival_order += 1
            elif command == "NEXT":
                next_email = inbox.peek()
                print("Next email:")
                print(next_email if next_email else "No emails to read.")
            elif command == "READ":
                read_email = inbox.pop()
                if not read_email:
                    print("No emails to read.")
            elif command == "COUNT":
                print(f"There are {len(inbox)} emails to read.")

def main ():
    process_commands("Assignment1_Test_File.txt")

main()

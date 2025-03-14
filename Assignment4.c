#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100  // Max number of emails that can be stored   
// thats the max num of emails to be stores - i think the define makes it a const

typedef struct { 
    char catSender[20];// category of the sender
    char subject[100]; // just the subject line
    char date[11];  // MM-DD-YYYY format
    int order; // order when it was receivved
    int priority; // diff prioity for diff senders
} EMAIL;


EMAIL heap[MAX_EMAILS]; // Max-Heap  and does the list based implementeation
int heapSize = 0;

 
int getPriority(const char *category) {  // this was on stack overflow but basically this determines the diff levels of priority 
    if (strcmp(category, "Boss") == 0) return 5; // boss is obviously the highest
    if (strcmp(category, "Subordinate") == 0) return 4; 
    if (strcmp(category, "Peer") == 0) return 3;
    if (strcmp(category, "ImportantPerson") == 0) return 2;  // down to 2 as per instrunctons
    return 1; // "OtherPerson" // randoms are a 1
}

// Swap function for heap
void swap(EMAIL *a, EMAIL *b) {
    EMAIL temp = *a; // this just makes a temp variable so that a and b can be swapped 
    *a = *b; // so you can swap 2 EMAIL structs in the heap
    *b = temp;
}


void upHeap(int index) {  // keep the  max-heap property after insertion
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].priority >= heap[parent].priority) {  // if the childs priority is higher than parents = SWAP
        if (heap[index].priority > heap[parent].priority || strcmp(heap[index].date, heap[parent].date) > 0) { // If priorities are the same, sort by date
            swap(&heap[index], &heap[parent]); // SWAP
        }
        index = parent; // change the indec
        parent = (index - 1) / 2;
    }
}


void downHeap(int index) { // this just puts the  the max-heap property  back after removing an email.
    int leftChild, rightChild, largest; // instantiate var to put  left and right child and var for largest
    while (1) {
        leftChild = 2 * index + 1; //Compares both left and right children to find the highest-priority email.
        rightChild = 2 * index + 2;
        largest = index;

        if (leftChild < heapSize && 
           (heap[leftChild].priority > heap[largest].priority || 
           (heap[leftChild].priority == heap[largest].priority && strcmp(heap[leftChild].date, heap[largest].date) > 0))) {
            largest = leftChild;
        }

        if (rightChild < heapSize && 
           (heap[rightChild].priority > heap[largest].priority || 
           (heap[rightChild].priority == heap[largest].priority && strcmp(heap[rightChild].date, heap[largest].date) > 0))) {
            largest = rightChild;
        }

        if (largest == index) break; // Swaps with the largest child until the heap is ordered correctly.


        swap(&heap[index], &heap[largest]);
        index = largest;
    }
}

void pushEmail(EMAIL email) { // Insert email into heap

    if (heapSize >= MAX_EMAILS) {
        printf("Heap is full, cannot add more emails.\n");
        return;
    }
    heap[heapSize] = email;
    upHeap(heapSize);
    heapSize++; // Adds an email to the heap and reorders it using upHeap().

}


EMAIL popEmail() { // Removes the highest-priority email (root of the heap).
    EMAIL empty = {"", "", "", -1, -1};
    if (heapSize == 0) return empty;

    EMAIL topEmail = heap[0];
    heap[0] = heap[--heapSize];  // Move last email to root
    downHeap(0); // Moves the last email to the root and restores order using downHeap().

    return topEmail;
}


EMAIL peekEmail() {
// Peek at the highest priority email
    if (heapSize == 0) {
        EMAIL empty = {"", "", "", -1, -1};
        return empty;
    }
    return heap[0]; // Returns the email with the highest priority without removing it.

}


void processCommands(const char *filename) { // Process commands from the input file
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256]; // 0 - 255 incl
    int order = 0;

    while (fgets(line, sizeof(line), file)) {
        char command[10], catSender[20], subject[100], date[11];

        if (sscanf(line, "%s", command) != 1) continue;

        if (strcmp(command, "EMAIL") == 0) {
            sscanf(line, "%*s %[^,], %[^,], %s", catSender, subject, date);

            EMAIL email;
            strcpy(email.catSender, catSender);
            strcpy(email.subject, subject);
            strcpy(email.date, date);
            email.order = order++;
            email.priority = getPriority(catSender);

            pushEmail(email);
        } 
        else if (strcmp(command, "NEXT") == 0) { //eads a file containing email-related commands (EMAIL, NEXT, READ, COUNT).
            EMAIL nextEmail = peekEmail();  // Processes each command and updates the heap
            if (nextEmail.order != -1) {
                printf("Next email:\nSender: %s\nSubject: %s\nDate: %s\n", 
                       nextEmail.catSender, nextEmail.subject, nextEmail.date);
            } else {
                printf("No emails.\n");
            }
        } 
        else if (strcmp(command, "READ") == 0) {
            EMAIL readEmail = popEmail();
            if (readEmail.order != -1) {
                printf("Reading email from: %s\n", readEmail.catSender);
            } else {
                printf("No emails.\n");
            }
        } 
        else if (strcmp(command, "COUNT") == 0) {
            printf("There are %d emails to read.\n", heapSize);
        }
    }

    fclose(file);
}


int main() {
    processCommands("Assignment4_Test_File.txt");
    return 0;
} // Calls processCommands() to process emails from the input file.

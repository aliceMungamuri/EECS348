#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100  // Max number of emails that can be stored

// Structure to store email information
typedef struct {
    char catSender[20];
    char subject[100];
    char date[11];  // MM-DD-YYYY format
    int order;
    int priority;
} EMAIL;

// Max-Heap (list-based) implementation
EMAIL heap[MAX_EMAILS];
int heapSize = 0;

// Priority Mapping
int getPriority(const char *category) {
    if (strcmp(category, "Boss") == 0) return 5;
    if (strcmp(category, "Subordinate") == 0) return 4;
    if (strcmp(category, "Peer") == 0) return 3;
    if (strcmp(category, "ImportantPerson") == 0) return 2;
    return 1; // "OtherPerson"
}

// Comparison function for sorting emails in priority order
int compareEmails(const void *a, const void *b) {
    EMAIL *emailA = (EMAIL *)a;
    EMAIL *emailB = (EMAIL *)b;

    if (emailA->priority != emailB->priority) 
        return emailB->priority - emailA->priority; // Higher priority first

    int dateCompare = strcmp(emailB->date, emailA->date); // Newest first
    if (dateCompare != 0) return dateCompare;

    return emailA->order - emailB->order; // Oldest first for same priority
}

// Insert email into heap
void pushEmail(EMAIL email) {
    if (heapSize >= MAX_EMAILS) {
        printf("Heap is full, cannot add more emails.\n");
        return;
    }
    heap[heapSize++] = email;
    qsort(heap, heapSize, sizeof(EMAIL), compareEmails);  // Maintain heap order
}

// Remove and return the highest priority email
EMAIL popEmail() {
    EMAIL empty = {"", "", "", -1, -1};
    if (heapSize == 0) return empty;

    EMAIL topEmail = heap[0];

    for (int i = 1; i < heapSize; i++) {
        heap[i - 1] = heap[i];  // Shift elements left
    }
    heapSize--;
    return topEmail;
}

// Peek at the highest priority email
EMAIL peekEmail() {
    if (heapSize == 0) {
        EMAIL empty = {"", "", "", -1, -1};
        return empty;
    }
    return heap[0];
}

// Process commands from the input file
void processCommands(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
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
        else if (strcmp(command, "NEXT") == 0) {
            EMAIL nextEmail = peekEmail();
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

// Main function
int main() {
    processCommands("Assignment4_Test_File.txt");
    return 0;
}

// EECS 348 Assignment 8
// Input: the test file
// Output: next email and email count
// Collaborators: None
// Other sources: code from  instructor
// Alice Mungamuri
/

#include <iostream> 
#include <vector> 
#include <string> 
#include <sstream> 
#include <algorithm> 
#include <iomanip> 
#include <map> 
#include <ctime> 
#include <fstream> 

using namespace std;

int arrivalCounter = 0; // global counter to keep track of email arrival order

// function to convert a string MM-DD-YYYY date to time_t
time_t parseDate(const string& dateStr) {
    struct tm tm{}; // create an empty tm struct to hold date values
    sscanf(dateStr.c_str(), "%d-%d-%d", &tm.tm_mon, &tm.tm_mday, &tm.tm_year); // read date values
    tm.tm_mon -= 1; // months are 0-indexed in struct tm
    tm.tm_year -= 1900; // years are counted from 1900 in struct tm
    return mktime(&tm); // convert struct tm to time_t
}

// map sender category to integer priority (higher = more important)
map<string, int> senderPriority = {
    {"Boss", 5},
    {"Subordinate", 4},
    {"Peer", 3},
    {"ImportantPerson", 2},
    {"OtherPerson", 1}
};

class Email {
public:
    string senderCategory; // sender category like Boss, Peer, etc.
    string subject; // subject of the email
    string dateStr; // string representation of date
    time_t date; // time object of date for comparison
    int arrivalOrder; // order in which email arrived

    // constructor to initialize email object
    Email(string sender, string subj, string date_string) {
        senderCategory = sender; // assign sender
        subject = subj; // assign subject
        dateStr = date_string; // assign date string
        date = parseDate(date_string); // parse date string
        arrivalOrder = arrivalCounter++; // assign and increment arrival order
    }

    // operator> overload for max-heap comparison
    bool operator>(const Email& other) const {
        if (senderPriority[senderCategory] != senderPriority[other.senderCategory])
            return senderPriority[senderCategory] > senderPriority[other.senderCategory]; // compare priority
        if (date != other.date)
            return date > other.date; // if same priority, compare dates
        return arrivalOrder < other.arrivalOrder; // if same date, newer arrival wins (lower number)
    }

    // print email info
    void display() const {
        cout << "Sender: " << senderCategory << endl; // print sender
        cout << "Subject: " << subject << endl; // print subject
        cout << "Date: " << dateStr << endl; // print date
    }
};

class MaxHeap {
private:
    vector<Email> heap; // vector to store heap of emails

    // move email up the heap to maintain max-heap property
    void heapifyUp(int idx) {
        while (idx > 0 && heap[idx] > heap[(idx - 1) / 2]) { // if current is greater than parent
            swap(heap[idx], heap[(idx - 1) / 2]); // swap with parent
            idx = (idx - 1) / 2; // move index to parent
        }
    }

    // move email down the heap to maintain max-heap property
    void heapifyDown(int idx) {
        int size = heap.size(); // get current size
        while (true) {
            int largest = idx; // initialize largest as root
            int left = 2 * idx + 1; // left child
            int right = 2 * idx + 2; // right child
            if (left < size && heap[left] > heap[largest]) largest = left; // compare with left child
            if (right < size && heap[right] > heap[largest]) largest = right; // compare with right child
            if (largest != idx) { // if not the largest, swap
                swap(heap[idx], heap[largest]);
                idx = largest; // update index to continue heapify
            } else {
                break; // heap property satisfied
            }
        }
    }

public:
    void push(const Email& email) {
        heap.push_back(email); // add email to heap
        heapifyUp(heap.size() - 1); // maintain heap property
    }

    Email peek() {
        if (!heap.empty()) return heap[0]; // return highest priority email
        throw runtime_error("No emails to read."); // throw if heap is empty
    }

    void pop() {
        if (heap.empty()) return; // if empty, do nothing
        heap[0] = heap.back(); // replace root with last
        heap.pop_back(); // remove last
        if (!heap.empty()) heapifyDown(0); // maintain heap property
    }

    int size() const {
        return heap.size(); // return number of emails
    }

    bool empty() const {
        return heap.empty(); // check if heap is empty
    }
};

class EmailManager {
private:
    MaxHeap heap; // max-heap of emails
    bool hasCurrent = false; // whether currentEmail is active
    Email currentEmail = Email("", "", "01-01-2000"); // placeholder

public:
    void processLine(const string& line) {
        if (line.rfind("EMAIL ", 0) == 0) { // if line starts with "EMAIL "
            string rest = line.substr(6); // remove "EMAIL " prefix
            stringstream ss(rest); // parse rest of line
            string sender, subject, date;
            getline(ss, sender, ','); // extract sender
            getline(ss, subject, ','); // extract subject
            getline(ss, date, ','); // extract date
            Email email(sender, subject, date); // create email object
            heap.push(email); // add to heap
        } else if (line == "COUNT") { // command to count emails
            cout << "There are " << heap.size() << " emails to read.\n" << endl;
        } else if (line == "NEXT") { // command to get next email
            if (!hasCurrent) { // only fetch if not already fetched
                if (!heap.empty()) {
                    currentEmail = heap.peek(); // get top email
                    hasCurrent = true; // mark as current
                }
            }
            if (hasCurrent) {
                cout << "Next email:" << endl;
                currentEmail.display(); // display current email
                cout << endl;
            } else {
                cout << "No emails to read.\n" << endl;
            }
        } else if (line == "READ") { // command to mark email as read
            if (hasCurrent) {
                heap.pop(); // remove current email
                hasCurrent = false; // reset
            } else if (!heap.empty()) {
                heap.pop(); // remove top email anyway
            }
        }
    }
};

// function to run the program using a file as input
void runFromFile(const string& filename) {
    ifstream infile(filename); // open file
    string line;
    EmailManager manager; // create manager
    while (getline(infile, line)) { // read each line
        if (!line.empty()) {
            manager.processLine(line); // process command
        }
    }
}

int main() {
    //D runFromFile("test.txt");
    runFromFile("Assignment8_Test_File.txt"); //A changed to use correct test file
    return 0; // return successful exit code
}

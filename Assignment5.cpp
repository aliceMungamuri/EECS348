#include <iostream> // input output operations
#include <fstream> // file read/write
#include <queue> // provide access to the priority_queue data structure
#include <string> // so you can use strings
#include <vector> //nor used in this code 
#include <sstream> //process strings like file lines

using namespace std; // we saw this in lab so std:: cout not necessary cout

struct Email {
    string catSender; // category of sender
    string subject; // subject of the email
    string date; // MM-DD-YYYY format
    int order; // order of the email received
    int priority; // higher num = higher priority

    // Operator overloading for priority queue (max-heap behavior)
    bool operator<(const Email& other) const {
        if (priority == other.priority) {
            return date < other.date; // Higher date means newer
        }
        return priority < other.priority; // Higher priority first
    }
};

int getPriority(const string& category) {
    if (category == "Boss") return 5; // highest to lowest - start at boss
    if (category == "Subordinate") return 4;
    if (category == "Peer") return 3;
    if (category == "ImportantPerson") return 2; //
    return 1; // "OtherPerson"
}

priority_queue<Email> emailQueue; // priority 

void pushEmail(const Email& email) { // this  function is made to insert the an Email into the priority queue
    emailQueue.push(email);
}

Email popEmail() {// removes at the top of the queue
    if (emailQueue.empty()) { //  from Stack overflow -  removes highest priority email basically if it is empty it returns a dummy email with the -1 values
        return {"", "", "", -1, -1};
    }
    Email topEmail = emailQueue.top();
    emailQueue.pop();
    return topEmail; // returns the topMail
}

Email peekEmail() { // returns the highest priority email - doesnt remove it
    if (emailQueue.empty()) {
        return {"", "", "", -1, -1}; // dummy email if stack is empty - basically 
    }
    return emailQueue.top();
}

void processCommands(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    int order = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "EMAIL") {
            string catSender, subject, date;
            getline(iss, catSender, ',');
            getline(iss, subject, ',');
            getline(iss, date);

            Email email{catSender, subject, date, order++, getPriority(catSender)};
            pushEmail(email);
        } else if (command == "NEXT") {
            Email nextEmail = peekEmail();
            if (nextEmail.order != -1) {
                cout << "Next email:\nSender: " << nextEmail.catSender << "\nSubject: " << nextEmail.subject << "\nDate: " << nextEmail.date << "\n";
            } else {
                cout << "No emails.\n";
            }
        } else if (command == "READ") {
            Email readEmail = popEmail();
            if (readEmail.order != -1) {
                cout << "Reading email from: " << readEmail.catSender << endl;
            } else {
                cout << "No emails.\n";
            }
        } else if (command == "COUNT") {
            cout << "There are " << emailQueue.size() << " emails to read.\n";
        }
    }
    file.close();
}

int main() {
    processCommands("Assignment4_Test_File.txt");
    return 0;
}

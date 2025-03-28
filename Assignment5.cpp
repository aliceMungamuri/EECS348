#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Email {
    string catSender;
    string subject;
    string date; // MM-DD-YYYY format
    int order;
    int priority;

    // Operator overloading for priority queue (max-heap behavior)
    bool operator<(const Email& other) const {
        if (priority == other.priority) {
            return date < other.date; // Higher date means newer
        }
        return priority < other.priority; // Higher priority first
    }
};

int getPriority(const string& category) {
    if (category == "Boss") return 5;
    if (category == "Subordinate") return 4;
    if (category == "Peer") return 3;
    if (category == "ImportantPerson") return 2;
    return 1; // "OtherPerson"
}

priority_queue<Email> emailQueue;

void pushEmail(const Email& email) {
    emailQueue.push(email);
}

Email popEmail() {
    if (emailQueue.empty()) {
        return {"", "", "", -1, -1};
    }
    Email topEmail = emailQueue.top();
    emailQueue.pop();
    return topEmail;
}

Email peekEmail() {
    if (emailQueue.empty()) {
        return {"", "", "", -1, -1};
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

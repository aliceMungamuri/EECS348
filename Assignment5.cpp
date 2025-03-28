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

void processCommands(const string& filename) { // void funct to process commands
    ifstream file(filename); // opens file with commands
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl; // error if cant be opened print that message and exits
        return;
    }

    string line; // var line is a string
    int order = 0; // init

    while (getline(file, line)) { // reads each line from file
        istringstream iss(line); // process line
        string command; // extracts first word for command
        iss >> command;

        if (command == "EMAIL") { // if to process email commad
            string catSender, subject, date; // EMAIL command parameters
            getline(iss, catSender, ',');
            getline(iss, subject, ',');
            getline(iss, date);

            Email email{catSender, subject, date, order++, getPriority(catSender)}; // EMAIL obj
            pushEmail(email); // insert into queue
        } else if (command == "NEXT") { // if next
            Email nextEmail = peekEmail(); // gets the next highest priority email in queu
            if (nextEmail.order != -1) {
                cout << "Next email:\nSender: " << nextEmail.catSender << "\nSubject: " << nextEmail.subject << "\nDate: " << nextEmail.date << "\n";
            } else { // cout abouve printed the sender subj and date
                cout << "No emails.\n"; // nothing there so print no emails
            }
        } else if (command == "READ") { // removes and processes the highest priority email
            Email readEmail = popEmail();
            if (readEmail.order != -1) { // starting from back
                cout << "Reading email from: " << readEmail.catSender << endl;
            } else {
                cout << "No emails.\n"; // nothing there = no emaile
            }
        } else if (command == "COUNT") { // just count
            cout << "There are " << emailQueue.size() << " emails to read.\n"; // print num of emails in the queue
        }
    }
    file.close(); // close file
}

int main() { // main funct
    processCommands("Assignment5_Test_File.txt");
    return 0; // close the program it ran
}

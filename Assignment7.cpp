// EECS 348 Assignment 7
// C++ MySQL Program to execute 12 SQL queries for database interaction
// Author: Alice Mungamuri
// KU ID: a911m624
// Created: April 24, 2025
// Collaborators: None
// Sources: ChatGPT, StackOverflow, MySQL Connector/C++ Docs
// Input: Connected database tables (Student, Course, Enrollment, Faculty, Offering)
// Output: Results of 12 queries printed to console

#include <iostream>
#include <stdexcept>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

void runQuery(Statement* stmt, const string& query, const string& label) {
    cout << "------ " << label << " ------" << endl;
    ResultSet* res = stmt->executeQuery(query);
    ResultSetMetaData* meta = res->getMetaData();
    int columns = meta->getColumnCount();
    while (res->next()) {
        for (int i = 1; i <= columns; ++i) {
            cout << res->getString(i) << "\t";
        }
        cout << endl;
    }
    delete res;
    cout << endl;
}

int main() {
    try {
        Driver* driver = get_driver_instance();
        Connection* con = driver->connect("tcp://127.0.0.1:3306", "root", "rootpass");
        con->setSchema("assignment7");

        Statement* stmt = con->createStatement();

        // Query 1
        runQuery(stmt,
            "SELECT StdFirstName, StdLastName FROM Student WHERE StdMajor = 'IS';",
            "Query 1: Students majoring in 'IS'");

        // Query 2
        runQuery(stmt,
            "SELECT StdNo FROM Enrollment GROUP BY StdNo HAVING COUNT(*) > 2;",
            "Query 2: Students enrolled in more than 2 courses");

        // Query 3
        runQuery(stmt,
            "SELECT FacFirstName, FacLastName FROM Faculty WHERE FacDept = 'Physics' AND FacHireDate <= DATE_SUB(CURDATE(), INTERVAL 5 YEAR);",
            "Query 3: Professors in 'Physics' > 5 years");

        // Query 4
        runQuery(stmt,
            "SELECT StdMajor, COUNT(*) AS NumStudents FROM Student GROUP BY StdMajor HAVING COUNT(*) > 50;",
            "Query 4: Departments with > 50 students");

        // Query 5
        runQuery(stmt,
            "SELECT Course.CourseNo, CrsDesc FROM Course JOIN Offering ON Course.CourseNo = Offering.CourseNo JOIN Faculty ON Offering.FacNo = Faculty.FacNo WHERE CrsDesc LIKE '%Data%' AND FacLastName = 'Johnson';",
            "Query 5: Courses with 'Data' taught by Dr. Johnson");

        // Query 6
        runQuery(stmt,
            "SELECT StdFirstName, StdLastName FROM Student WHERE StdNo NOT IN (SELECT DISTINCT StdNo FROM Enrollment WHERE OfferNo IN (SELECT OfferNo FROM Offering WHERE OffYear >= 2023));",
            "Query 6: Students not enrolled in last 2 semesters");

        // Query 7
        runQuery(stmt,
            "SELECT MAX(StdGPA) FROM Student WHERE StdGPA < (SELECT MAX(StdGPA) FROM Student);",
            "Query 7: Second-highest GPA");

        // Query 8
        runQuery(stmt,
            "SELECT s.StdFirstName, s.StdLastName FROM Student s JOIN Faculty f ON s.StdNo = f.FacNo WHERE s.StdGPA > 3.5;",
            "Query 8: Students who are TAs with GPA > 3.5");

        // Query 9
        runQuery(stmt,
            "SELECT s.StdFirstName, s.StdLastName, c.CrsDesc FROM Student s JOIN Enrollment e ON s.StdNo = e.StdNo JOIN Offering o ON e.OfferNo = o.OfferNo JOIN Course c ON o.CourseNo = c.CourseNo WHERE o.OffYear > 2022;",
            "Query 9: Enrollments after 2022");

        // Query 10
        runQuery(stmt,
            "SELECT FacFirstName, FacLastName, FacSalary FROM Faculty ORDER BY FacSalary DESC LIMIT 3;",
            "Query 10: Top 3 highest-paid professors");

        // Query 11
        stmt->execute("INSERT INTO Student VALUES ('888-88-8888', 'Alice', 'Smith', 'Topeka', 'KS', '66610', 'CS', 'JR', 3.85);");
        runQuery(stmt,
            "SELECT * FROM Student WHERE StdNo = '888-88-8888';",
            "Query 11: Inserted Alice Smith");

        // Query 12
        stmt->execute("UPDATE Student SET StdCity = 'Overland Park', StdZip = '66204' WHERE StdFirstName = 'BOB' AND StdLastName = 'NORBERT';");
        runQuery(stmt,
            "SELECT * FROM Student WHERE StdFirstName = 'BOB' AND StdLastName = 'NORBERT';",
            "Query 12: Updated Bob Norbert");

        delete stmt;
        delete con;

    } catch (SQLException& e) {
        cerr << "SQL error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

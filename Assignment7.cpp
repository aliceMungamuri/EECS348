// EECS 348 Assignment 7
// Database Query Integration via MySQL Connector
// Inputs: No input file, runs SQL commands against preloaded tables
// Output: Console output of query results
// Collaborators: None
// Other sources: MySQL Connector/C++ documentation, ChatGPT
// Author: Alice J Mungamuri
// Creation date: April 24, 2025

#include <iostream>
#include <stdexcept>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

using namespace std;
using namespace sql;

// Utility function to run and print SQL queries
void runQuery(Connection* conn, const string& query, const string& description) {
    try {
        Statement* stmt = conn->createStatement();
        ResultSet* res = stmt->executeQuery(query);

        cout << "\n--- " << description << " ---\n";
        ResultSetMetaData* meta = res->getMetaData();
        int cols = meta->getColumnCount();

        while (res->next()) {
            for (int i = 1; i <= cols; i++) {
                cout << meta->getColumnLabel(i) << ": " << res->getString(i) << " | ";
            }
            cout << endl;
        }

        delete res;
        delete stmt;
    } catch (SQLException& e) {
        cerr << "Error running query: " << e.what() << endl;
    }
}

int main() {
    try {
        mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();
        Connection* conn = driver->connect("tcp://127.0.0.1:3306", "root", "rootpass");

        // Replace with your database name (e.g., use 348s25_lxxxxxxx)
        conn->setSchema("assignment7");

        runQuery(conn, "SELECT * FROM Student WHERE StdMajor = 'IS';",
                 "Students majoring in IS");

        runQuery(conn,
                 "SELECT StdFirstName, StdLastName FROM Student WHERE StdNo IN "
                 "(SELECT StdNo FROM Enrollment GROUP BY StdNo HAVING COUNT(*) > 2);",
                 "Students enrolled in more than two courses");

        runQuery(conn,
                 "SELECT FacFirstName, FacLastName FROM Faculty "
                 "WHERE FacDept = 'Physics' AND FacHireDate < DATE_SUB(CURDATE(), INTERVAL 5 YEAR);",
                 "Professors with 5+ years in Physics");

        runQuery(conn,
                 "SELECT StdMajor, COUNT(*) AS Total FROM Student GROUP BY StdMajor HAVING COUNT(*) > 50;",
                 "Departments with more than 50 students");

        runQuery(conn,
                 "SELECT C.CourseNo, C.CrsDesc FROM Course C JOIN Offering O ON C.CourseNo = O.CourseNo "
                 "JOIN Faculty F ON O.FacNo = F.FacNo "
                 "WHERE C.CrsDesc LIKE '%Data%' AND F.FacLastName = 'Johnson';",
                 "Courses with 'Data' taught by Dr. Johnson");

        runQuery(conn,
                 "SELECT StdFirstName, StdLastName FROM Student "
                 "WHERE StdNo NOT IN (SELECT StdNo FROM Enrollment "
                 "WHERE OffYear >= 2023);",
                 "Students not enrolled in the past two semesters");

        runQuery(conn,
                 "SELECT MAX(StdGPA) FROM Student WHERE StdGPA < "
                 "(SELECT MAX(StdGPA) FROM Student);",
                 "Second-highest GPA");

        runQuery(conn,
                 "SELECT StdFirstName, StdLastName FROM Student S JOIN Faculty F ON S.StdNo = F.FacNo "
                 "WHERE StdGPA > 3.5;",
                 "Students who are also teaching assistants with GPA > 3.5");

        runQuery(conn,
                 "SELECT S.StdFirstName, S.StdLastName, C.CourseNo FROM Student S "
                 "JOIN Enrollment E ON S.StdNo = E.StdNo "
                 "JOIN Offering O ON E.OfferNo = O.OfferNo "
                 "JOIN Course C ON O.CourseNo = C.CourseNo "
                 "WHERE O.OffYear > 2022;",
                 "Students enrolled after 2022 and their courses");

        runQuery(conn,
                 "SELECT FacFirstName, FacLastName, FacSalary FROM Faculty "
                 "ORDER BY FacSalary DESC LIMIT 3;",
                 "Top 3 highest-paid professors");

        Statement* stmt = conn->createStatement();
        stmt->execute("INSERT INTO Student (StdNo, StdFirstName, StdLastName, StdCity, StdState, StdZip, StdMajor, StdClass, StdGPA) "
                      "VALUES ('888-88-8888', 'Alice', 'Smith', 'Topeka', 'KS', '66610', 'CS', 'JR', 3.85);");
        runQuery(conn, "SELECT * FROM Student WHERE StdNo = '888-88-8888';", "Inserted Alice Smith");

        stmt->execute("UPDATE Student SET StdCity = 'Overland Park', StdZip = '66204' WHERE StdFirstName = 'Bob' AND StdLastName = 'Norbert';");
        runQuery(conn, "SELECT * FROM Student WHERE StdFirstName = 'Bob' AND StdLastName = 'Norbert';", "Updated Bob Norbert");

        delete stmt;
        delete conn;

    } catch (SQLException& e) {
        cerr << "Database error: " << e.what() << endl;
    }

    return 0;
}

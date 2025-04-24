// EECS 348 Assignment 7
// Author: Alice Mungamuri
// Description: Executes 12 SQL queries using MySQL Connector/C++ and outputs the results
// Inputs: No external input file needed
// Output: Query results printed to terminal
// Collaborators: None
// Sources: ChatGPT, MySQL documentation
// Created: April 24, 2025

#include <iostream>
#include <stdexcept>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>
#include <mysql_connection.h>

void runQuery(sql::Connection* conn, const std::string& label, const std::string& query) {
    try {
        std::cout << "\n--- " << label << " ---\n";
        sql::Statement* stmt = conn->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);

        int columns = res->getMetaData()->getColumnCount();
        while (res->next()) {
            for (int i = 1; i <= columns; ++i) {
                std::cout << res->getMetaData()->getColumnLabel(i) << ": " << res->getString(i) << " | ";
            }
            std::cout << "\n";
        }
        delete res;
        delete stmt;
    } catch (sql::SQLException& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
    }
}

int main() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* conn = driver->connect("tcp://127.0.0.1:3306", "root", "rootpass");
        conn->setSchema("assignment7");

        runQuery(conn, "1. Students majoring in IS", 
            "SELECT StdFirstName, StdLastName FROM Student WHERE StdMajor = 'IS'");

        runQuery(conn, "2. Students in more than two courses", 
            "SELECT StdNo FROM Enrollment GROUP BY StdNo HAVING COUNT(*) > 2");

        runQuery(conn, "3. Professors in Physics for over 5 years", 
            "SELECT FacFirstName, FacLastName FROM Faculty WHERE FacDept = 'Physics' AND FacHireDate < DATE_SUB(CURDATE(), INTERVAL 5 YEAR)");

        runQuery(conn, "4. Departments with more than 50 students", 
            "SELECT StdMajor, COUNT(*) AS Total FROM Student GROUP BY StdMajor HAVING COUNT(*) > 50");

        runQuery(conn, "5. Courses with 'Data' taught by Dr. Johnson", 
            "SELECT Course.CourseNo, CrsDesc FROM Course JOIN Offering ON Course.CourseNo = Offering.CourseNo JOIN Faculty ON Offering.FacNo = Faculty.FacNo WHERE CrsDesc LIKE '%Data%' AND FacLastName = 'Johnson'");

        runQuery(conn, "6. Students not enrolled in last two semesters", 
            "SELECT * FROM Student WHERE StdNo NOT IN (SELECT DISTINCT StdNo FROM Enrollment)");

        runQuery(conn, "7. Second-highest GPA", 
            "SELECT MAX(StdGPA) AS SecondHighestGPA FROM Student WHERE StdGPA < (SELECT MAX(StdGPA) FROM Student)");

        runQuery(conn, "8. Students who are TAs with GPA > 3.5", 
            "SELECT StdFirstName, StdLastName FROM Student WHERE StdGPA > 3.5 AND StdNo IN (SELECT DISTINCT FacNo FROM Faculty)");

        runQuery(conn, "9. Students enrolled after 2022 and their courses", 
            "SELECT s.StdFirstName, s.StdLastName, c.CrsDesc FROM Student s JOIN Enrollment e ON s.StdNo = e.StdNo JOIN Offering o ON e.OfferNo = o.OfferNo JOIN Course c ON o.CourseNo = c.CourseNo WHERE o.OffYear > 2022");

        runQuery(conn, "10. Top 3 highest-paid professors", 
            "SELECT FacFirstName, FacLastName, FacSalary FROM Faculty ORDER BY FacSalary DESC LIMIT 3");

        runQuery(conn, "11. Insert student Alice Smith", 
            "INSERT INTO Student (StdNo, StdFirstName, StdLastName, StdCity, StdState, StdZip, StdMajor, StdClass, StdGPA) VALUES ('888-88-8888', 'Alice', 'Smith', 'Topeka', 'KS', '66610', 'CS', 'JR', 3.85)");
        runQuery(conn, "11b. Confirm Alice Smith Insert", 
            "SELECT * FROM Student WHERE StdNo = '888-88-8888'");

        runQuery(conn, "12. Update Bob Norbert's address", 
            "UPDATE Student SET StdCity = 'Overland Park', StdZip = '66204' WHERE StdFirstName = 'BOB' AND StdLastName = 'NORBERT'");
        runQuery(conn, "12b. Confirm Bob Norbert Update", 
            "SELECT * FROM Student WHERE StdFirstName = 'BOB' AND StdLastName = 'NORBERT'");

        delete conn;
    } catch (sql::SQLException& e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

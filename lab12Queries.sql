SELECT StdFirstName, StdLastName, StdCity, StdGPA
FROM Student
WHERE StdGPA > 3.7;

SELECT StdFirstName, StdLastName, StdGPA
FROM Student
ORDER BY StdGPA DESC;

SELECT *
FROM Course
WHERE CourseNo LIKE 'IS4%';

SELECT OfferNo, CourseNo
FROM Offering
WHERE OffTerm = 'SUMMER' AND FacNo IS NULL;

SELECT o.OfferNo, o.CourseNo, f.FacFirstName, f.FacLastName
FROM Offering o
JOIN Faculty f ON o.FacNo = f.FacNo
WHERE o.OffTerm = 'SPRING' AND f.FacRank = 'ASST';

SELECT DISTINCT FacNo
FROM Offering;

SELECT StdFirstName AS FirstName
FROM Student
WHERE StdCity = 'Bothell'
UNION
SELECT FacFirstName
FROM Faculty
WHERE FacCity = 'Bellevue';

INSERT INTO Student
(StdNo, StdFirstName, StdLastName, StdCity, StdState, StdZip, StdMajor, StdClass, StdGPA)
VALUES ('999-99-9999', 'John', 'Doe', 'Lawrence', 'KS', '66045', 'FIN', 'FR', 4.0);

SELECT * FROM Student;

UPDATE Student
SET StdMajor = 'ACCT'
WHERE StdFirstName = 'HOMER' AND StdLastName = 'WELLS';

SELECT * FROM Student;

SELECT *
FROM Student
WHERE StdNo IN (SELECT FacNo FROM Faculty);

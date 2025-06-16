#include <iostream>
#include <vector>
#include "student.h"
#include "subject.h"
#include "grade.h"
#include "report_utils.h"
#include "classroom.h"
#include <chrono>
#include <thread>
using namespace std;

// declarations
void saveStudentsToFile(const vector<Student>&, const string&);
vector<Student> loadStudentsFromFile(const string&);
void addStudent(vector<Student>&);
void listStudents(const vector<Student>&);
void editStudent(vector<Student>&);
void deleteStudent(vector<Student>&);

void addClassroom(vector<Classroom>&, const vector<Student>&);
void saveClassroomsToFile(const vector<Classroom>&, const string&);
vector<Classroom> loadClassroomsFromFile(const string&);



void slowPrint(const string& text, int delayMs = 1) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

void showIntro() {
    string logo = R"(
 
___________           ________                  .___    ___.                  __    
\_   _____/          /  _____/___________     __| _/____\_ |__   ____   ____ |  | __
 |    __)_   ______ /   \  __\_  __ \__  \   / __ |/ __ \| __ \ /  _ \ /  _ \|  |/ /
 |        \ /_____/ \    \_\  \  | \// __ \_/ /_/ \  ___/| \_\ (  <_> |  <_> )    < 
/_______  /          \______  /__|  (____  /\____ |\___  >___  /\____/ \____/|__|_ \
        \/                  \/           \/      \/    \/    \/                   \/

    )";

    slowPrint(logo, 1);
    cout << "\nWelcome to the digital gradebook system! 🎓📘\n\n";
}

int main() {
    vector<Student> students = loadStudentsFromFile("students.txt");
    vector<Subject> subjects = loadSubjectsFromFile("subjects.txt");
    vector<Grade> grades = loadGradesFromFile("grades.txt");
    vector<Classroom> classrooms = loadClassroomsFromFile("classrooms.txt");

    showIntro();
    int choice;
    do {
        cout << "+=======================================================+\n";
        cout << "|             WELCOME TO SCHOOL GRADEBOOK v1.0          |\n";
        cout << "+=====================[ MAIN MENU ]=====================+\n";
        cout << "| 1. Add student            | 2. Show all students      |\n";
        cout << "| 3. Edit student           | 4. Delete student         |\n";
        cout << "|--------------------------|----------------------------|\n";
        cout << "| 5. Add subject            | 6. Show all subjects      |\n";
        cout << "| 7. Edit subject           | 8. Delete subject         |\n";
        cout << "|--------------------------|----------------------------|\n";
        cout << "| 9. Add grade              | 10. Show all grades       |\n";
        cout << "| 11. Edit grade            | 12. Delete grade          |\n";
        cout << "|--------------------------|----------------------------|\n";
        cout << "| 13. Avg grade in subject                              |\n";
        cout << "| 14. Avg grade overall                                 |\n";
        cout << "| 15. Top students (>5.50)                              |\n";
        cout << "| 16. Remedial (<3.00)                                  |\n";
        cout << "| 17. <3.00 in 3+ subjects                              |\n";
        cout << "| 18. Birthdays today                                   |\n";
        cout << "|--------------------------|----------------------------|\n";
        cout << "| 19. Create classroom      | 20. List classrooms       |\n";
        cout << "| 21. Edit classroom                                    |\n";
        cout << "| 22. Delete classroom                                  |\n";
        cout << "| 0. Exit                                               |\n";
        cout << "+=======================================================+\n";
        cout << "Select option: ";


        cin >> choice;
        cin.ignore();


        switch (choice) {
        case 1:
            addStudent(students);
            saveStudentsToFile(students, "students.txt");
            break;
        case 2:
            listStudents(students);
            break;
        case 3:
            editStudent(students);
            saveStudentsToFile(students, "students.txt");
            break;
        case 4:
            deleteStudent(students);
            saveStudentsToFile(students, "students.txt");
            break;
        case 5:
            addSubject(subjects);
            saveSubjectsToFile(subjects, "subjects.txt");
            break;
        case 6:
            listSubjects(subjects);
            break;
        case 7:
            editSubject(subjects);
            saveSubjectsToFile(subjects, "subjects.txt");
            break;
        case 8:
            deleteSubject(subjects);
            saveSubjectsToFile(subjects, "subjects.txt");
            break;
        case 9:
            addGrade(grades, students, subjects);
            saveGradesToFile(grades, "grades.txt");
            break;
        case 10:
            listGrades(grades, students);
            break;
        case 11:
            editGrade(grades, students, subjects);
            saveGradesToFile(grades, "grades.txt");
            break;
        case 12:
            deleteGrade(grades, students);
            saveGradesToFile(grades, "grades.txt");
            break;
        case 13:
            averageGradePerSubject(grades, students, subjects);
            break;
        case 14:
            averageGradeAllSubjects(grades, students);
             break;
        case 15:
            listTopStudents(grades, students);
            break;
        case 16:
            listRemedialStudents(grades, students);
            break;
        case 17:
            listStudentsWithThreeFails(grades, students);
            break;
        case 18:
            listBirthdaysToday(students);
            break;
        case 19:
            addClassroom(classrooms, students);
            saveClassroomsToFile(classrooms, "classrooms.txt");
            break;
        case 20:
            listClassrooms(classrooms, students);
            break;
        case 21:
            editClassroom(classrooms, students);
            break;
        case 22:
            deleteClassroom(classrooms, students);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

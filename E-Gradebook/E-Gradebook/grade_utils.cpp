#include "grade.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void saveGradesToFile(const vector<Grade>& grades, const string& filename) {
    ofstream file(filename);
    for (const auto& g : grades) {
        file << g.id << ";"
            << g.studentId << ";"
            << g.subjectName << ";"
            << g.value << ";"
            << g.date << "\n";
    }
    file.close();
}

vector<Grade> loadGradesFromFile(const string& filename) {
    vector<Grade> grades;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        Grade g;
        stringstream ss(line);
        string part;

        getline(ss, part, ';'); g.id = stoi(part);
        getline(ss, part, ';'); g.studentId = stoi(part);
        getline(ss, part, ';'); g.subjectName = part;
        getline(ss, part, ';'); g.value = stof(part);
        getline(ss, part, ';'); g.date = part;

        grades.push_back(g);
    }
    return grades;
}

void addGrade(vector<Grade>& grades, const vector<Student>& students, const vector<Subject>& subjects) {
    Grade g;
    g.id = grades.empty() ? 1 : grades.back().id + 1;

    cout << "\nAvailable students:\n";
    for (const auto& s : students) {
        cout << "ID: " << s.id << " | Name: " << s.fullName << "\n";
    }

    cout << "Enter student ID: ";
    cin >> g.studentId;
    cin.ignore();

    cout << "\nAvailable subjects:\n";
    for (const auto& sub : subjects) {
        cout << "- " << sub.name << "\n";
    }

    cout << "Enter subject name: ";
    getline(cin, g.subjectName);

    cout << "Enter grade (2.00 - 6.00): ";
    cin >> g.value;
    cin.ignore();

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, g.date);

    grades.push_back(g);
    cout << " Grade added successfully!\n";
}

void listGrades(const vector<Grade>& grades, const vector<Student>& students) {
    cout << "\n--- All Grades ---\n";
    for (const auto& g : grades) {
        string studentName = "Unknown";

        for (const auto& s : students) {
            if (s.id == g.studentId) {
                studentName = s.fullName;
                break;
            }
        }

        cout << "Grade ID: " << g.id
            << " | Student: " << studentName
            << " | Subject: " << g.subjectName
            << " | Grade: " << fixed << setprecision(2) << g.value
            << " | Date: " << g.date << "\n";
    }
    cout << "------------------\n";
}

void editGrade(vector<Grade>& grades, const vector<Student>& students, const vector<Subject>& subjects) {
    int id;
    cout << "Enter grade ID to edit: ";
    cin >> id;
    cin.ignore();

    for (auto& g : grades) {
        if (g.id == id) {
            cout << "Editing grade ID #" << g.id << "\n";

            cout << "Enter new student ID: ";
            cin >> g.studentId;
            cin.ignore();

            cout << "Enter new subject name: ";
            getline(cin, g.subjectName);

            cout << "Enter new grade (2.00 - 6.00): ";
            cin >> g.value;
            cin.ignore();

            cout << "Enter new date (YYYY-MM-DD): ";
            getline(cin, g.date);

            cout << "✅ Grade updated.\n";
            return;
        }
    }
    cout << " Grade not found.\n";
}

void deleteGrade(vector<Grade>& grades, const vector<Student>& students) {
    cout << "\n--- All Grades ---\n";
    for (const auto& g : grades) {
        string studentName = "Unknown";
        for (const auto& s : students) {
            if (s.id == g.studentId) {
                studentName = s.fullName;
                break;
            }
        }

        cout << "ID: " << g.id
            << " | Student: " << studentName
            << " | Subject: " << g.subjectName
            << " | Grade: " << fixed << setprecision(2) << g.value
            << " | Date: " << g.date << "\n";
    }
    cout << "------------------\n";

    int id;
    cout << "Enter grade ID to delete: ";
    cin >> id;

    auto it = remove_if(grades.begin(), grades.end(),
        [id](const Grade& g) { return g.id == id; });

    if (it != grades.end()) {
        grades.erase(it, grades.end());
        cout << " Grade deleted.\n";
    }
    else {
        cout << " Grade not found.\n";
    }
}






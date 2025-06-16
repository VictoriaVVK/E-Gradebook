#include "student.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits> // for cin.ignore fix
using namespace std;

void saveStudentsToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    for (const auto& s : students) {
        file << s.id << ";"
            << s.numberInClass << ";"
            << s.fullName << ";"
            << s.dateOfBirth << ";"
            << s.classId << "\n";  // ⬅️ добавено
    }
    file.close();
}

vector<Student> loadStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Student s;
        stringstream ss(line);
        string part;

        getline(ss, part, ';'); s.id = stoi(part);
        getline(ss, part, ';'); s.numberInClass = stoi(part);
        getline(ss, part, ';'); s.fullName = part;
        getline(ss, part, ';'); s.dateOfBirth = part;

        if (getline(ss, part, ';')) {
            s.classId = stoi(part); 
        }
        else {
            s.classId = -1; 
        }

        students.push_back(s);
    }
    return students;
}

void addStudent(vector<Student>& students) {
    Student s;
    s.id = students.empty() ? 1 : students.back().id + 1;

    cout << "Enter student number in class: ";
    while (!(cin >> s.numberInClass)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    // clear buffer

    cout << "Enter full name: ";
    getline(cin, s.fullName);
    while (s.fullName.empty()) {
        cout << "Name cannot be empty. Please enter full name: ";
        getline(cin, s.fullName);
    }

    cout << "Enter date of birth (YYYY-MM-DD): ";
    getline(cin, s.dateOfBirth);

    students.push_back(s);
    cout << " Student added successfully!\n";
}

void editStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID of student to edit: ";
    cin >> id;
    cin.ignore();

    for (auto& s : students) {
        if (s.id == id) {
            cout << "Editing student: " << s.fullName << "\n";

            cout << "New number in class: ";
            cin >> s.numberInClass;
            cin.ignore();

            cout << "New full name: ";
            getline(cin, s.fullName);

            cout << "New date of birth (YYYY-MM-DD): ";
            getline(cin, s.dateOfBirth);

            cout << " Student updated.\n";
            return;
        }
    }
    cout << " No student found with ID " << id << ".\n";
}

void deleteStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID of student to delete: ";
    cin >> id;

    auto it = remove_if(students.begin(), students.end(),
        [id](const Student& s) { return s.id == id; });

    if (it != students.end()) {
        students.erase(it, students.end());
        cout << " Student deleted.\n";
    }
    else {
        cout << " No student found with ID " << id << ".\n";
    }
}


void listStudents(const vector<Student>& students) {
    cout << "\n--- Student List ---\n";
    for (const auto& s : students) {
        cout << "ID: " << s.id
            << " | Number: " << s.numberInClass
            << " | Name: " << s.fullName
            << " | DOB: " << s.dateOfBirth << "\n";
    }
    cout << "---------------------\n";
}

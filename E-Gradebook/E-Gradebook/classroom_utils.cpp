#include "classroom.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <sstream>

void addClassroom(vector<Classroom>& classrooms,  vector<Student>& students) {
    Classroom c;
    c.id = classrooms.empty() ? 1 : classrooms.back().id + 1; // Автоматичен ID

    cout << "Enter class name (e.g. 12A): ";
    getline(cin, c.name);

    cout << "Enter class teacher full name: ";
    getline(cin, c.classTeacher);

    // Показваме само свободни ученици
    cout << "\nAvailable students (not assigned to any class):\n";
    for (const auto& s : students) {
        if (s.classId == -1) {
            cout << "ID: " << s.id << " | Name: " << s.fullName << "\n";
        }
    }

    cout << "\nEnter student IDs for this class (end with -1):\n";
    int id;
    while (true) {
        cout << "ID: ";
        cin >> id;
        if (id == -1) break;

        // Проверяваме дали ученикът е свободен
        auto it = find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.id == id && s.classId == -1; });

        if (it != students.end()) {
            it->classId = c.id;
            c.studentIds.push_back(id);
        }
        else {
            cout << " Invalid or already assigned student ID.\n";
        }
    }
    cin.ignore();

    classrooms.push_back(c);
    cout << "Classroom created and students assigned!\n";
}


void saveClassroomsToFile(const vector<Classroom>& classrooms, const string& filename) {
    ofstream file(filename);
    for (const auto& c : classrooms) {
        file << c.name << ";" << c.classTeacher;
        for (int id : c.studentIds) file << ";" << id;
        file << "\n";
    }
    file.close();
}

vector<Classroom> loadClassroomsFromFile(const string& filename) {
    vector<Classroom> classrooms;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string part;
        Classroom c;
        getline(ss, c.name, ';');
        getline(ss, c.classTeacher, ';');
        while (getline(ss, part, ';')) c.studentIds.push_back(stoi(part));
        classrooms.push_back(c);
    }
    return classrooms;
}

void listClassrooms(const vector<Classroom>& classrooms, const vector<Student>& students) {
    if (classrooms.empty()) {
        cout << "❗ No classrooms have been created yet.\n";
        return;
    }

    cout << "\n=== CLASSROOM LIST ===\n";
    for (const auto& c : classrooms) {
        cout << "Class: " << c.name << "\n";
        cout << "Class Teacher: " << c.classTeacher << "\n";
        cout << "Students:\n";

        for (int id : c.studentIds) {
            auto it = find_if(students.begin(), students.end(),
                [id](const Student& s) { return s.id == id; });

            if (it != students.end()) {
                cout << " - " << it->fullName << " (ID: " << it->id << ")\n";
            }
            else {
                cout << " - [Unknown student ID: " << id << "]\n";
            }
        }

        cout << "-------------------------\n";
    }
}

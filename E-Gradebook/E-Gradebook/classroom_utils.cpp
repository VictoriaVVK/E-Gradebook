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
        file << c.id << ";" << c.name << ";" << c.classTeacher;
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
        getline(ss, part, ';');
        c.id = stoi(part); // 🛠️ прочети ID-то
        getline(ss, c.name, ';');
        getline(ss, c.classTeacher, ';');
        while (getline(ss, part, ';')) c.studentIds.push_back(stoi(part));
        classrooms.push_back(c);
    }
    return classrooms;
}


void listClassrooms(const vector<Classroom>& classrooms, const vector<Student>& students) {
    if (classrooms.empty()) {
        cout << " No classrooms have been created yet.\n";
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

void editClassroom(vector<Classroom>& classrooms, vector<Student>& students) {
    if (classrooms.empty()) {
        cout << " No classrooms available to edit.\n";
        return;
    }

    cout << "\nAvailable Classrooms:\n";
    for (const auto& c : classrooms) {
        cout << "ID: " << c.id << " | Class: " << c.name << " | Teacher: " << c.classTeacher << "\n";
    }

    int classId;
    cout << "Enter the ID of the classroom to edit: ";
    cin >> classId;
    cin.ignore();

    auto it = find_if(classrooms.begin(), classrooms.end(),
        [classId](const Classroom& c) { return c.id == classId; });

    if (it == classrooms.end()) {
        cout << " No such classroom found.\n";
        return;
    }

    Classroom& c = *it;

    cout << "\nCurrent students in " << c.name << ":\n";
    for (int id : c.studentIds) {
        auto st = find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.id == id; });
        if (st != students.end()) {
            cout << " - " << st->fullName << " (ID: " << st->id << ")\n";
        }
    }

    cout << "\nAvailable students to add:\n";
    for (const auto& s : students) {
        if (s.classId == -1) {
            cout << "ID: " << s.id << " | Name: " << s.fullName << "\n";
        }
    }

    cout << "\nEnter student IDs to add (end with -1):\n";
    int id;
    while (true) {
        cout << "ID: ";
        cin >> id;
        if (id == -1) break;

        auto st = find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.id == id && s.classId == -1; });

        if (st != students.end()) {
            st->classId = c.id;
            c.studentIds.push_back(id);
            cout << " Added " << st->fullName << " to " << c.name << "\n";
        }
        else {
            cout << " Invalid or already assigned.\n";
        }
    }
    cin.ignore();
    cout << " Classroom updated.\n";
}

void deleteClassroom(vector<Classroom>& classrooms, vector<Student>& students) {
    if (classrooms.empty()) {
        cout << " No classrooms to delete.\n";
        return;
    }

    cout << "\n=== CLASSROOMS ===\n";
    for (const auto& c : classrooms) {
        cout << "ID: " << c.id << " | Name: " << c.name << "\n";
    }

    cout << "Enter ID of classroom to delete: ";
    int delId;
    cin >> delId;
    cin.ignore();

    auto it = find_if(classrooms.begin(), classrooms.end(),
        [delId](const Classroom& c) { return c.id == delId; });

    if (it != classrooms.end()) {
        
        for (auto& s : students) {
            if (s.classId == delId) s.classId = -1;
        }

        classrooms.erase(it);
        cout << " Classroom deleted and students unassigned.\n";
    }
    else {
        cout << " No such classroom ID.\n";
    }
}

#include "subject.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;

void saveSubjectsToFile(const vector<Subject>& subjects, const string& filename) {
    ofstream file(filename);
    for (const auto& s : subjects) {
        file << s.id << ";" << s.name << ";" << s.teacherFullName << ";" << s.roomNumber << "\n";
    }
    file.close();
}

vector<Subject> loadSubjectsFromFile(const string& filename) {
    vector<Subject> subjects;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Subject s;
        stringstream ss(line);
        string part;

        getline(ss, part, ';'); s.id = stoi(part);
        getline(ss, part, ';'); s.name = part;
        getline(ss, part, ';'); s.teacherFullName = part;
        getline(ss, part, ';'); s.roomNumber = part;

        subjects.push_back(s);
    }
    return subjects;
}

void addSubject(vector<Subject>& subjects) {
    Subject s;
    s.id = subjects.empty() ? 1 : subjects.back().id + 1;

    cout << "Enter subject name: ";
    getline(cin, s.name);

    cout << "Enter teacher full name: ";
    getline(cin, s.teacherFullName);

    cout << "Enter room number: ";
    getline(cin, s.roomNumber);

    subjects.push_back(s);
    cout << "✅ Subject added successfully!\n";
}

void listSubjects(const vector<Subject>& subjects) {
    cout << "\n--- Subject List ---\n";
    for (const auto& s : subjects) {
        cout << "ID: " << s.id
            << " | Name: " << s.name
            << " | Teacher: " << s.teacherFullName
            << " | Room: " << s.roomNumber << "\n";
    }
    cout << "---------------------\n";
}

void editSubject(vector<Subject>& subjects) {
    string name;
    cout << "Enter subject name to edit: ";
    getline(cin, name);

    for (auto& s : subjects) {
        if (s.name == name) {
            cout << "Editing subject: " << s.name << "\n";

            cout << "New teacher name: ";
            getline(cin, s.teacherFullName);

            cout << "New room number: ";
            getline(cin, s.roomNumber);

            cout << "✅ Subject updated.\n";
            return;
        }
    }
    cout << "❌ Subject not found.\n";
}

void deleteSubject(vector<Subject>& subjects) {
    string name;
    cout << "Enter subject name to delete: ";
    getline(cin, name);

    auto it = remove_if(subjects.begin(), subjects.end(),
        [name](const Subject& s) { return s.name == name; });

    if (it != subjects.end()) {
        subjects.erase(it, subjects.end());
        cout << "✅ Subject deleted.\n";
    }
    else {
        cout << "❌ Subject not found.\n";
    }
}

#pragma once
#include <string>
#include <vector>
using namespace std;

struct Subject {
    int id;
    string name;
    string teacherFullName;
    string roomNumber;
};

void saveSubjectsToFile(const vector<Subject>&, const string&);
vector<Subject> loadSubjectsFromFile(const string&);
void addSubject(vector<Subject>&);
void listSubjects(const vector<Subject>&);
void editSubject(vector<Subject>&);
void deleteSubject(vector<Subject>&);


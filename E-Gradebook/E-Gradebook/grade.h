#pragma once
#include <string>
#include <vector>
#include "student.h"
#include "subject.h"

using namespace std;

struct Grade {
    int id; //to identify which grade to change/delete
    int studentId;  //classnumber of student
    string subjectName; 
    float value;          //(2-6)
    string date;        
};


void saveGradesToFile(const vector<Grade>&, const string&);
vector<Grade> loadGradesFromFile(const string&);
void addGrade(vector<Grade>&, const vector<Student>&, const vector<Subject>&);
void listGrades(const vector<Grade>&, const vector<Student>&);
void editGrade(vector<Grade>&, const vector<Student>&, const vector<Subject>&);
void deleteGrade(vector<Grade>&, const vector<Student>&);


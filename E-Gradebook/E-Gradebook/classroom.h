#pragma once
#include <string>
#include <vector>
#include "student.h"
using namespace std;

struct Classroom {
    int id;
    string name; 
    string classTeacher;
    vector<int> studentIds; 
};

void listClassrooms(const vector<Classroom>&, const vector<Student>&);
void addClassroom(vector<Classroom>&,  vector<Student>&);

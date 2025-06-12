#pragma once
#include <vector>
#include <string>
#include "student.h"
#include "subject.h"
#include "grade.h"

using namespace std;

void averageGradePerSubject(const vector<Grade>&, const vector<Student>&);
void averageGradeAllSubjects(const vector<Grade>&, const vector<Student>&);
void listTopStudents(const vector<Grade>&, const vector<Student>&);
void listRemedialStudents(const vector<Grade>&, const vector<Student>&);
void listStudentsWithThreeFails(const vector<Grade>&, const vector<Student>&);
void listBirthdaysToday(const vector<Student>&);

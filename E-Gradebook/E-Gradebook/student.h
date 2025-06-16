#pragma once
#include <string>
using namespace std;

struct Student {
    int id;
    int numberInClass;
    string fullName;
    string dateOfBirth;
    int classId = -1; // By default, student has no class
};
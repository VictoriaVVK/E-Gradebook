#include "report_utils.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <ctime>

using namespace std;

void averageGradePerSubject(const vector<Grade>& grades, const vector<Student>& students) {
    int studentId;
    string subjectName;
    cout << "Enter student ID: ";
    cin >> studentId;
    cin.ignore();
    cout << "Enter subject name: ";
    getline(cin, subjectName);

    float sum = 0;
    int count = 0;
    for (const auto& g : grades) {
        if (g.studentId == studentId && g.subjectName == subjectName) {
            sum += g.value;
            count++;
        }
    }

    if (count > 0) {
        cout << "Average grade in " << subjectName << " is: " << fixed << setprecision(2) << (sum / count) << endl;
    }
    else {
        cout << "No grades found for that student and subject.\n";
    }
}

void averageGradeAllSubjects(const vector<Grade>& grades, const vector<Student>& students) {
    int studentId;
    cout << "Enter student ID: ";
    cin >> studentId;

    float sum = 0;
    int count = 0;
    for (const auto& g : grades) {
        if (g.studentId == studentId) {
            sum += g.value;
            count++;
        }
    }

    if (count > 0) {
        cout << "Overall average: " << fixed << setprecision(2) << (sum / count) << endl;
    }
    else {
        cout << "No grades for that student.\n";
    }
}

void listTopStudents(const vector<Grade>& grades, const vector<Student>& students) {
    map<int, pair<float, int>> studentStats; // id -> {sum, count}

    for (const auto& g : grades) {
        studentStats[g.studentId].first += g.value;
        studentStats[g.studentId].second++;
    }

    cout << "Top students (> 5.50):\n";
    for (const auto& [id, stat] : studentStats) {
        float avg = stat.first / stat.second;
        if (avg > 5.50f) {
            for (const auto& s : students) {
                if (s.id == id) {
                    cout << s.fullName << " (avg: " << fixed << setprecision(2) << avg << ")\n";
                }
            }
        }
    }
}

void listRemedialStudents(const vector<Grade>& grades, const vector<Student>& students) {
    cout << "Remedial students (grade < 3.00):\n";
    for (const auto& g : grades) {
        if (g.value < 3.00f) {
            for (const auto& s : students) {
                if (s.id == g.studentId) {
                    cout << s.fullName << " - Subject: " << g.subjectName << ", Grade: " << g.value << endl;
                }
            }
        }
    }
}

void listStudentsWithThreeFails(const vector<Grade>& grades, const vector<Student>& students) {
    map<int, int> failCounts;
    for (const auto& g : grades) {
        if (g.value < 3.00f) {
            failCounts[g.studentId]++;
        }
    }

    cout << "Students with 3+ fails:\n";
    for (const auto& [id, count] : failCounts) {
        if (count >= 3) {
            for (const auto& s : students) {
                if (s.id == id) {
                    cout << s.fullName << " - Fails: " << count << endl;
                }
            }
        }
    }
}

void listBirthdaysToday(const vector<Student>& students) {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int day = now->tm_mday;
    int month = now->tm_mon + 1;

    cout << "Students with birthday today (" << setfill('0') << setw(2) << day << "/" << setw(2) << month << "):\n";
    for (const auto& s : students) {
        if (s.dateOfBirth.length() >= 10) {
            int dobMonth = stoi(s.dateOfBirth.substr(5, 2));
            int dobDay = stoi(s.dateOfBirth.substr(8, 2));

            if (dobDay == day && dobMonth == month) {
                cout << s.fullName << " (" << s.dateOfBirth << ")\n";
            }
        }
    }
}

//
// Created by peng on 2023/4/29.
//

#ifndef STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_STUDENT_H
#define STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_STUDENT_H
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Student {
public:
    Student(const string& name) : name_(name) {}
    string GetName() const { return name_; }
    void AddScore(const string& subject, double score) { scores_[subject] = score; }
    double GetScore(const string& subject) const;
    vector<string> GetSubjects() const;
    void PrintAllScores() const;

private:
    string name_;
    std::unordered_map<string, double> scores_;
};

class Score {
public:
    Score(const string& name, const string& subject, double score) : name_(name), subject_(subject), score_(score) {}
    string GetName() const { return name_; }
    string GetSubject() const { return subject_; }
    double GetScore() const { return score_; }

private:
    string name_;
    string subject_;
    double score_;
};

#endif //STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_STUDENT_H

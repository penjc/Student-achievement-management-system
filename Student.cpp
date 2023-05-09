//
// Created by peng on 2023/4/29.
//
#include "Student.h"
double Student::GetScore(const string& subject) const{
    auto it = scores_.find(subject);
    if (it == scores_.end()) {
        return -1; // -1 表示缺省成绩
    } else {
        return it->second;
    }
}

vector<string> Student::GetSubjects() const{
    vector<string> subject;
    for (const auto& score : scores_) {
        subject.push_back(score.first);
    }
    return subject;
}

void Student::PrintAllScores() const{
    for (const auto &score: scores_) {
        if(score.second>=0) {
            cout << score.first << ": " << score.second << endl;
        }
    }
}
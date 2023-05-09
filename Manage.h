//
// Created by peng on 2023/4/29.
//
#ifndef STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_MANAGE_H
#define STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_MANAGE_H
#include <iostream>
#include <vector>
#include "Student.h"

using namespace std;
class Manage {
public:
    ~Manage(){for (auto it : students) delete it;}
    // 添加学生信息
    void AddStudent(const string& line);
    // 从命令行读取成绩
    void LoadScoresFromCommandLine();
    // 从文件读取成绩
    void LoadScoresFromFile(const string& filename);
    // 按科目输出成绩（成绩高至低）
    void PrintScoresByOneSubject(const std::string& subject) const;
    // 输出所有科目成绩（成绩高至低）
    void PrintScoresByAllSubject() const;
    // 输出某科目最高分
    void PrintMaxScoreBySubject(const string& subject) const;
    // 输出某科目最低分
    void PrintMinScoreBySubject(const string& subject) const;
    // 输出某科目平均分
    void PrintAverageScoreByOneSubject(const string& subject) const;
    // 输出所有科目平均分
    void PrintAverageScoreByAllSubjects() const;
    // 修改成绩
    void ModifyScore();
    // 查找某科目缺省成绩
    void FindMissingScores(const string subject) const;
    // 查找所有缺省成绩
    void FindAllMissingScores() const;
private:
    vector<Student*> students;
};
#endif //STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_MANAGE_H

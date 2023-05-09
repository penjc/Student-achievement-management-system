//
// Created by peng on 2023/4/29.
//
#include <sstream>
#include <fstream>
#include "Manage.h"

string Subjects[] = {"语文","数学","英语","物理"};

void Manage::AddStudent(const string& line){
    istringstream iss(line);
    string name, subject;
    double score;
    while (iss >> name >> subject >> score) {
        bool subexists = false;
        for (const auto& s :Subjects){
            if (s == subject) {
                subexists = true;
                break;
            }
        }
        if (!subexists) {
            cerr << "请输入正确的科目" << endl << endl;
            return;
        }
        if(score<-1 || score >100) {
            cerr << "请输入正确的成绩（0~100）" << endl << endl;
            return;
        }
        bool student_exists = false;
        //若成绩存在，退出循环
        for(auto it : students) {
            if (it->GetName() == name){
                if(it->GetScore(subject)>0){
                    cerr<<name<<subject<<"成绩存在"<<endl<<endl;
                    student_exists = true;
                    break;
                }
                else{
                    it->AddScore(subject, score);
                    student_exists = true;
                    break;
                }
            }
        }
        if(!student_exists){
            auto *p = new Student(name);
            p->AddScore(subject, score);
            students.push_back(p);
        }
    }
}

void Manage::LoadScoresFromCommandLine(){
    cout<<"请输入："<<"\n"<<"姓名 科目 成绩"<<endl;
    string name, subject;
    double score;
    cin>>name>>subject>>score;
    if(score<-1 || score >100) {
        cerr << "请输入正确的成绩（0~100）" << endl << endl;
        return;
    }
    bool subexists = false;
    for (const auto& s :Subjects){
        if (s == subject) {
            subexists = true;
            break;
        }
    }
    if (!subexists) {
        cerr<< "请输入正确的科目" << endl << endl;
        return;
    }
    bool student_exists = false;
    //若成绩存在，退出循环
    for(auto it : students) {
        if (it->GetName() == name){
            if(it->GetScore(subject)>=0){
                cerr<<name<<subject<<"成绩已存在"<<endl<<endl;
                student_exists = true;
                break;
            }
            else{
                it->AddScore(subject, score);
                cout << "录入完成" << endl << endl;
                student_exists = true;
                break;
            }
        }
    }
    if(!student_exists){
        auto *p = new Student(name);
        p->AddScore(subject, score);
        students.push_back(p);
        cout << "录入完成" << endl << endl;
    }
}


void Manage::LoadScoresFromFile(const std::string& filename){
    ifstream ifs;
    ifs.open(filename, ios::in);	//打开文件
    if (!ifs.is_open()) { // 检查文件是否成功打开
        cerr << "无法打开文件" << endl;
        return ;
    }
    string line;
    while (getline(ifs, line)) {
        cout<<line<<endl;
        AddStudent(line);
    }
}

void Manage::PrintScoresByOneSubject(const string &subject) const{
    bool subexists = false;
    for (const auto& s :Subjects){
        if (s == subject) {
            subexists = true;
            break;
        }
    }
    if (!subexists) {
        cerr << "请输入正确的科目" << endl << endl;
        return;
    }
    vector<Score> scores;
    bool subject_exists = false; // add a flag to check if the subject exists
    for (const auto& student : students) {
        double score = student->GetScore(subject);
        if (score >= 0) {
            scores.push_back(Score(student->GetName(), subject, score));
            subject_exists = true; // set the flag to true if a score is found
        }
    }
    if (!subject_exists) { // if no score is found, print a message and return
        cerr << "成绩缺省" << endl << endl;
        return;
    }
    std::sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) { return a.GetScore() > b.GetScore(); });
    auto it = scores.begin();
    cout<<subject<<":"<<endl;
    for (const auto& score : scores) {
        cout << score.GetName() << "  " << score.GetScore() << endl ;
    }
    cout<<endl;
}


void Manage::PrintScoresByAllSubject() const{
    vector<Score> scores;
    for (const auto& student : students) {
        for (const auto& subject : student->GetSubjects()) {
            double score = student->GetScore(subject);
            if (score >= 0.0) {
                scores.push_back(Score(student->GetName(), subject, score));
            }
        }
    }
    std::sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) {
        if (a.GetSubject() == b.GetSubject()) {
            return a.GetScore() > b.GetScore();
        }
        return a.GetSubject() < b.GetSubject();
    });
    string last_subject = "";
    for (const auto& score : scores) {
        if (score.GetSubject() != last_subject) {
            cout << endl; // add a new line if the subject changes
            last_subject = score.GetSubject();
        }
        cout << score.GetName() << "  " << score.GetSubject() << " " << score.GetScore() << endl;
    }
    cout<<endl;
}

void Manage::PrintMaxScoreBySubject(const string& subject) const{
//    vector<string> s{"语文","数学","英语"};
//    auto it = s.begin();
//    for(;it!=s.end();++it){
//        if(*it==subject)
//            break;
//    }
//    if(it==s.end()){
//        cout << "请输入正确的科目" << endl<<endl;return ;
//    }
    bool subject_exists = false;
    for (const auto& s :Subjects){
        if (s == subject) {
            subject_exists = true;
            break;
        }
    }
    if (!subject_exists) {
        cerr << "请输入正确的科目" << endl << endl;
        return;
    }
        double max_score = -1;
        std::string max_name;
        for (const auto& student : students) {
            double score = student->GetScore(subject);
            if (score > max_score) {
                max_score = score;
                max_name = student->GetName();
            }
        }
        if(max_score>=0){
            cout  << subject << "最高成绩是 " << max_name << " ：" << max_score << endl << endl;
        }
        else{
            cerr <<"成绩缺省"<<endl<<endl;
        }
}

void Manage::PrintMinScoreBySubject(const string& subject) const{
    bool subexists = false;
    for (const auto& s :Subjects){
        if (s == subject) {
            subexists = true;
            break;
        }
    }
    if (!subexists) {
        cerr << "请输入正确的科目" << endl << endl;
        return;
    }
    double min_score = numeric_limits<double>::max();
    string min_name;
    for (const auto& student : students) {
        double score = student->GetScore(subject);
        if (score < min_score && score >0.0) {
            min_score = score;
            min_name = student->GetName();
        }
        else if(score == 0.0 && min_score == numeric_limits<double>::max()){
            min_score = score;
            min_name = student->GetName();
        }
        else if(score == 0.0 && min_score > 0.0){
            min_score = score;
            min_name = student->GetName();
        }
    }
    if(min_score==numeric_limits<double>::max()){
        cerr<<"成绩缺省"<<endl<<endl;
        return ;
    }
    cout  << subject << "最低成绩是 " << min_name << " ：" << min_score << endl << endl;
}

void Manage::PrintAverageScoreByOneSubject(const string& subject) const{
    bool subexists = false;
    for (const auto& s :Subjects){
        if (s == subject) {
            subexists = true;
            break;
        }
    }
    if (!subexists) {
        cerr << "请输入正确的科目" << endl << endl;
        return;
    }
    double sum_score = 0.0;
    int count_score = 0;
    bool all_missing = true; // flag to check if all scores are missing
    for (const auto& student : students) {
        double score = student->GetScore(subject);
        if (score >= 0.0) {
            sum_score += score;
            count_score++;
            all_missing = false; // if there is at least one score, set flag to false
        }
    }
    if (all_missing) { // if all scores are missing
        cerr <<subject<< "成绩缺省" << endl <<endl;
    } else if (count_score > 0) {
        cout << subject << "平均成绩是 " << sum_score / count_score << endl <<endl;
    } else {
        cerr <<subject<< "成绩缺省" << endl <<endl;
    }
}

void Manage::PrintAverageScoreByAllSubjects() const{
    for(auto& sub : Subjects)
        PrintAverageScoreByOneSubject(sub);
}

void Manage::ModifyScore(){
    cout<<"请输入："<<"\n"<<"姓名 科目 成绩"<<endl;
    string n, sub;
    double sc;
    cin >>n>>sub>>sc;
    bool subexists = false;
    for (const auto& s :Subjects){
        if (s == sub) {
            subexists = true;
            break;
        }
    }
    if (!subexists) {
        cerr << "请输入正确的科目" << endl << endl;
        return;
    }
    if(sc<-1 || sc >100) {
        cerr << "请输入正确的成绩（0~100）" << endl << endl;
        return;
    }
    bool found_student = false; // flag to check if student is found
    for (auto& student : students) {
        if (student->GetName() == n) {
            student->AddScore(sub, sc );
            found_student = true; // set flag to true if student is found
            break;
        }
    }
    if (found_student) { // if student is found
        cout<<"修改成功"<<endl<<endl;
    } else { // if student is not found
        cerr<<"没有该学生"<<endl<<endl;
    }
}


void Manage::FindMissingScores(const string subject) const{
    for (const auto& student : students) {
        if (student->GetScore(subject) == -1) {
            cerr<< student->GetName() <<"的"<< subject <<"成绩缺省"<< endl;
        }
    }
}

void Manage::FindAllMissingScores() const{
    for(auto& sub : Subjects)
        FindMissingScores(sub);
    cout<<"查找完毕"<<endl<<endl;
}
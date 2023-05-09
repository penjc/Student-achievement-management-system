#include <iostream>
#include <iomanip>
#include "Manage.h"
#include "Timer.h"
#include "ManagePlugin.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
void print(){
    cout <<setw(8)<< BLUE << "请选择您要进行的操作：" << RESET << endl;
    cout << "1. " << GREEN << "命令行录入成绩" << RESET << endl;
    cout << "2. " << GREEN << "文件录入成绩" << RESET << endl;
    cout << "3. " << GREEN << "单科目最高分" << RESET << endl;
    cout << "4. " << GREEN << "单科目最低分" << RESET << endl;
    cout << "5. " << GREEN << "单科成绩对同学姓名排序" << RESET << endl;
    cout << "6. " << GREEN << "所有科目对同学姓名排序" << RESET << endl;
    cout << "7. " << GREEN << "各科目平均分" << RESET << endl;
    cout << "8. " << GREEN << "所有科目平均分" << RESET << endl;
    cout << "9. " << GREEN << "修改成绩" << RESET << endl;
    cout << "a. " << CYAN  << "加载查找分数缺省插件" << RESET << endl;
    cout << "b. " << CYAN  << "加载定时查找分数缺省插件" << RESET << endl;
    cout << "c. " << CYAN  << "执行查找分数缺省插件" << RESET << endl;
    cout << "d. " << CYAN  << "执行定时查找分数缺省插件" << RESET << endl;
    cout << "e. " << RED   << "卸载查找分数缺省插件" << RESET << endl;
    cout << "f. " << RED   << "卸载定时查找分数缺省插件" << RESET << endl;
    cout << "0. " << RED   << "退出程序" << RESET << endl;
}
int main() {
    cout << setw(10)<< BLUE << "学生成绩管理系统" << RESET << endl;
    Manage m;
    PluginManager MissingScore;
    PluginManager Timer;

//    MissingScore.LoadPlugin(make_unique<FindAllMissingScoresPlugin>());
//    Timer.LoadPlugin(make_unique<TimerPlugin>(3));

    m.AddStudent("王五 语文 67\n王五 英语 0\n赵六 语文 76\n赵六 数学 85\n赵六 英语 91\n孙七 语文 89\n孙七 数学 90\n孙七 英语 92\n");
    string sub;
    string filename;
//    Timer timer(chrono::seconds(3), [&]() {
//        std::cout << "查找分数缺省...\n";
//        m.FindAllMissingScores();
//    });
//    timer.Start();
    while(true)
    {

        print();
        char t;
        cin>>t;
        switch (t)
        {
            case '1'://命令行录入成绩
                m.LoadScoresFromCommandLine();
                break;
            case '2'://文件录入成绩
                cout<<"请输入文件路径"<<endl;
                cin >> filename;
                m.LoadScoresFromFile(filename);
                break;
            case '3'://单科目最高分
                cout<<"请输入您查询的科目"<<endl;
                cin>>sub;
                m.PrintMaxScoreBySubject(sub);
                break;
            case '4'://单科目最低分
                cout<<"请输入您查询的科目"<<endl;
                cin>>sub;
                m.PrintMinScoreBySubject(sub);
                break;
            case '5'://单科成绩对同学姓名排序
                cout<<"请输入您查询的科目"<<endl;
                cin>>sub;
                m.PrintScoresByOneSubject(sub);
                break;
            case '6'://所有科目对同学姓名排序
                m.PrintScoresByAllSubject();
                break;
            case '7'://各科目平均分
                cout<<"请输入您查询的科目"<<endl;
                cin>>sub;
                m.PrintAverageScoreByOneSubject(sub);
                break;
            case '8'://所有科目平均分
                m.PrintAverageScoreByAllSubjects();
                break;
            case '9'://修改成绩
                m.ModifyScore();
                break;
            case 'a'://查找分数缺省插件
                MissingScore.LoadPlugin(make_unique<FindAllMissingScoresPlugin>());

                break;
            case 'b'://定时查找分数缺省插件
                Timer.LoadPlugin(make_unique<TimerPlugin>(3));
                break;
            case 'c':
                MissingScore.ExecuteAll(m);
                break;
            case 'd':
                Timer.ExecuteAll(m);
                break;
            case 'e':
                MissingScore.UnloadPlugin(0);
                break;
            case 'f':
                Timer.UnloadPlugin(0);
                break;
            case '0'://退出
//                timer.Stop();
                MissingScore.UnloadPlugin(0);
                Timer.UnloadPlugin(0);
                m.~Manage();
                return 0;
            default:
                break;
        }
    }
    MissingScore.UnloadPlugin(0);
    Timer.UnloadPlugin(0);
    return 0;
}

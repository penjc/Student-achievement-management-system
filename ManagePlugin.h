//
// Created by peng on 2023/4/29.
//

#ifndef STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_MANAGEPLUGIN_H
#define STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_MANAGEPLUGIN_H
#include "Manage.h"
#include "Timer.h"
class ManagePlugin {
public:
    virtual void Execute(Manage& m) = 0;
};
class FindAllMissingScoresPlugin : public ManagePlugin{
public:
    virtual void Execute(Manage& m) override{
        m.FindAllMissingScores();
    }
};
class TimerPlugin : public ManagePlugin{
public:
    explicit TimerPlugin(int intervalInSeconds) : m_interval(intervalInSeconds){}

    virtual void Execute(Manage& m) {
        thread([&]() {
            while (true) {
                this_thread::sleep_for(chrono::seconds(m_interval));
                m.FindAllMissingScores();
            }
        }).detach();
    }

private:
    int m_interval;
};


class PluginManager {
public:
    void LoadPlugin(std::unique_ptr<ManagePlugin> plugin){
        m_plugins.push_back(std::move(plugin));
        cout<<"插件已加载"<<endl;
    }

    void UnloadPlugin(size_t index){
        if (index >= m_plugins.size()){
            throw std::out_of_range("Plugin index out of range");
        }
        if (m_plugins[index] != nullptr) {
            m_plugins.erase(m_plugins.begin() + index);
            cout << "插件已被卸载" << endl;
        }
    }

    void ExecuteAll(Manage& m) {
        if (m_plugins.empty()) {
            cout << "插件未被上传，无法执行" << endl << endl;
            return;
        }
        for (auto& plugin : m_plugins){
            plugin->Execute(m);
        }
        cout<<"插件已执行"<<endl<<endl;
    }

private:
    vector<unique_ptr<ManagePlugin>> m_plugins;
};

#endif //STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_MANAGEPLUGIN_H

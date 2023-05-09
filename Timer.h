//
// Created by peng on 2023/4/29.
//
#ifndef STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_TIMER_H
#define STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_TIMER_H
#include <thread>
#include <utility>
using namespace std;
class Timer {
public:
    Timer(chrono::duration<long long int> interval_ms, function<void()> callback)
            : interval_ms_(interval_ms), callback_(move(callback)){}

    void Start(){
        thread_ = thread([this]{
            while (!stop_) {
                this_thread::sleep_for(chrono::milliseconds(interval_ms_));
                callback_();
            }
        });
    }
    void Stop(){
        stop_ = true;
        if (thread_.joinable()){
            thread_.join();
        }
    }
private:
    chrono::duration<long long int> interval_ms_;
    function<void()> callback_;
    thread thread_;
    atomic<bool> stop_{false};
};

#endif //STUDENT_ACHIEVEMENT_MANAGEMENT_SYSTEM_TIMER_H

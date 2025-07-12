#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

class Clock {
public:
    Clock() : alarm_set(false), alarm_hour(0), alarm_minute(0) {}

    virtual int get_hours() const {
        time_t current_time = time(0);
        tm local_time;
        localtime_s(&local_time, &current_time);
        return local_time.tm_hour;
    }

    virtual int get_minutes() const {
        time_t current_time = time(0);
        tm local_time;
        localtime_s(&local_time, &current_time);
        return local_time.tm_min;
    }

    string get_time() {
        int current_hour = get_hours();
        int current_minute = get_minutes();

        ostringstream oss;
        oss << setw(2) << setfill('0') << current_hour << ":"
            << setw(2) << setfill('0') << current_minute;

        if (alarm_set && is_alarm_time(current_hour, current_minute)) {
            alarm_set = false;
            oss << " Alarm";
        }

        return oss.str();
    }

    void set_alarm(int hours, int minutes) {
        alarm_hour = hours;
        alarm_minute = minutes;
        alarm_set = true;
    }

protected:
    mutable bool alarm_set;
    mutable int alarm_hour;
    mutable int alarm_minute;

    bool is_alarm_time(int current_hour, int current_minute) const {
        return (current_hour > alarm_hour ||
            (current_hour == alarm_hour && current_minute >= alarm_minute));
    }
};

class WorldClock : public Clock {
public:
    WorldClock(int offset_hours) : offset(offset_hours) {}

    int get_hours() const override {
        int local_hour = Clock::get_hours();
        return (local_hour + offset + 24) % 24;
    }

    int get_minutes() const override {
        return Clock::get_minutes();
    }

private:
    int offset;
};

int main() {
    Clock local_clock;
    local_clock.set_alarm(8, 0);

    cout << "Local time:      " << local_clock.get_time() << endl;

    WorldClock ny_clock(3);
    ny_clock.set_alarm(11, 0);

    cout << "New York time:   " << ny_clock.get_time() << endl;

    return 0;
}

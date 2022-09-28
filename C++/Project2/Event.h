#ifndef PROJECT2_EVENT_H
#define PROJECT2_EVENT_H
#include <iostream>
#include "Passenger.h"
using namespace std;

class Event{
public:
    enum Type{
        ARRIVAL=1,
        LUGGAGE=2,
        SECURITY=3,
    };
    Event(Type _type, Passenger _passenger, int _time);
    Event(const Event& event);
    Event& operator = (const Event& event);
    bool operator < (const Event& other)const;
    bool operator > (const Event& other)const;
    ~Event();
    int getTime()const;
    void setTime(int _time);
    Type type;
    Passenger passenger;

private:
    int time;

};

#endif //PROJECT2_EVENT_H

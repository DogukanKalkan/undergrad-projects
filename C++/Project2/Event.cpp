#include "Event.h"

Event::Event(Type _type, Passenger _passenger, int _time) {
    type = _type;
    passenger = _passenger;
    time = _time;
}

Event::Event(const Event& event) {
    type = event.type;
    passenger = event.passenger;
    time = event.time;
}

Event& Event::operator=(const Event &event) {
    type = event.type;
    passenger = event.passenger;
    time = event.time;
}

Event::~Event() {

}

bool Event::operator<(const Event& other)const {
    if(time == other.time){
        return type < other.type;
    }
    return time > other.getTime();
}
//bool Event::operator > (const Event& other)const{
//    if(time == other.time){
//        return type > other.type;
//    }
//    return time < other.getTime();
//}
int Event::getTime()const {
    return time;
}

void Event::setTime(int _time) {
    time = _time;
}
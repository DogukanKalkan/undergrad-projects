#ifndef PROJECT2_EVENTEXECUTER_H
#define PROJECT2_EVENTEXECUTER_H
#include <iostream>
#include "Event.h"
#include <queue>
using namespace std;

class EventExecuter{
public:
    EventExecuter( int _lugCounter, int _secCounter);
    void execute(int& caseNum);
    void executeArrival(Event &currentEvent, int& caseNum);
    void executeLuggage(Event &currentEvent, int& caseNum);
    void executeSecurity(Event &currentEvent, int& caseNum);

    priority_queue<Event> eventQueue;
    queue<Passenger> lugQueue;
    queue<Passenger> secQueue;
    priority_queue<Passenger> priorityLugQueue;
    priority_queue<Passenger> prioritySecQueue;
    int currentLugCounter;
    int currentSecCounter;
    int lugCounter;
    int secCounter;
    int timeOfLastEvent;
    int currentTime;
    int totalTime;
    int numOfLatePassengers;


};



#endif //PROJECT2_EVENTEXECUTER_H

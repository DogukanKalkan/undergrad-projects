#include "EventExecuter.h"

EventExecuter::EventExecuter( int _lugCounter, int _secCounter){
    numOfLatePassengers = 0;
    currentLugCounter = 0;
    currentSecCounter = 0;
    lugCounter = _lugCounter;
    secCounter = _secCounter;
    timeOfLastEvent = 0; currentTime = 0; totalTime = 0;
    priority_queue<Event> eventQueue = priority_queue<Event>();
    queue<Passenger> lugQueue = queue<Passenger>();
    queue<Passenger> secQueue = queue<Passenger>();
    priority_queue<Passenger> priorityLugQueue = priority_queue<Passenger>();
    priority_queue<Passenger> prioritySecQueue = priority_queue<Passenger>();
}

void EventExecuter::execute(int& caseNum) {
    Event currentEvent = eventQueue.top(); eventQueue.pop();
    timeOfLastEvent = eventQueue.empty() ? 0 : currentEvent.getTime();
    int qSize = eventQueue.size();
    currentTime += currentEvent.getTime();
    queue<Event> tmpQueue;
    for(int i=0 ; i < qSize; i++){
        Event e = eventQueue.top(); eventQueue.pop();
        e.setTime(e.getTime()-timeOfLastEvent);
        tmpQueue.push(e);
    }
    for(int i = 0; i < qSize; i++){
        eventQueue.push(tmpQueue.front()); tmpQueue.pop();
    }
    if(currentEvent.type == Event::Type::ARRIVAL){
        executeArrival(currentEvent, caseNum);
    }else if(currentEvent.type == Event::Type::LUGGAGE){
        executeLuggage(currentEvent, caseNum);

    }else{
        executeSecurity(currentEvent, caseNum);
    }
}

void EventExecuter::executeArrival(Event &currentEvent, int &caseNum) {
    Passenger p = currentEvent.passenger;
    switch(caseNum){
        case 1:
        case 3:
            if(currentLugCounter < lugCounter && lugQueue.empty()){
                Event newEvent(Event::Type::LUGGAGE, p, p.luggageTime);
                eventQueue.push(newEvent);
                currentLugCounter++;
            }
            else{
                lugQueue.push(p);
            }
            break;
        case 2:
        case 4:
            if(currentLugCounter < lugCounter && priorityLugQueue.empty()){
                Event newEvent(Event::Type::LUGGAGE, p, p.luggageTime);
                eventQueue.push(newEvent);
                currentLugCounter++;
            }
            else{
                priorityLugQueue.push(p);
            }
            break;
        case 5:
            if(p.hasLuggage){
                if(currentLugCounter < lugCounter && lugQueue.empty()){
                    Event newEvent(Event::Type::LUGGAGE, p, p.luggageTime);
                    eventQueue.push(newEvent);
                    currentLugCounter++;
                }
                else{
                    lugQueue.push(p);
                }
            }
            else{
                if(currentSecCounter < secCounter && secQueue.empty()){
                    Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                    eventQueue.push(newEvent);
                    currentSecCounter++;
                }
                else{
                    secQueue.push(p);
                }
            }
            break;
        case 6:
            if(p.hasLuggage){
                if(currentLugCounter < lugCounter && priorityLugQueue.empty()){
                    Event newEvent(Event::Type::LUGGAGE, p, p.luggageTime);
                    eventQueue.push(newEvent);
                    currentLugCounter++;
                }
                else{
                    priorityLugQueue.push(p);
                }
            }
            else{
                if(currentSecCounter < secCounter && prioritySecQueue.empty()){
                    Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                    eventQueue.push(newEvent);
                    currentSecCounter++;
                }
                else{
                    prioritySecQueue.push(p);
                }
            }
            break;
        case 7:
            if(p.hasLuggage){
                if(currentLugCounter < lugCounter && lugQueue.empty()){
                    Event newEvent(Event::Type::LUGGAGE, p, p.luggageTime);
                    eventQueue.push(newEvent);
                    currentLugCounter++;
                }
                else{
                    lugQueue.push(p);
                }
            }
            else{
                if(p.isVip){
                    if(currentTime > p.departureTime) numOfLatePassengers++;
                }
                else{
                    if(currentSecCounter < secCounter && secQueue.empty()){
                        Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                        eventQueue.push(newEvent);
                        currentSecCounter++;
                    }
                    else{
                        secQueue.push(p);
                    }
                }
            }
            break;
        case 8:
            if(p.hasLuggage){
                if(currentLugCounter < lugCounter && priorityLugQueue.empty()){
                    Event newEvent(Event::Type::LUGGAGE, p, p.luggageTime);
                    eventQueue.push(newEvent);
                    currentLugCounter++;
                }
                else{
                    prioritySecQueue.push(p);
                }
            }
            else{
                if(p.isVip){
                    if(currentTime > p.departureTime) numOfLatePassengers++;
                }
                else {
                    if(currentSecCounter < secCounter && prioritySecQueue.empty()){
                        Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                        eventQueue.push(newEvent);
                        currentSecCounter++;
                    }
                    else{
                        prioritySecQueue.push(p);
                    }
                }
            }
            break;
    }
}

void EventExecuter::executeLuggage(Event &currentEvent, int &caseNum) {
    Passenger p = currentEvent.passenger;
    currentLugCounter--;
    switch(caseNum){
        case 1:
            if(currentSecCounter < secCounter && secQueue.empty()){
                Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                eventQueue.push(newEvent);
                currentSecCounter++;
            }else{
                secQueue.push(p);
            }
            if(!lugQueue.empty()){
                Passenger nextPassenger = lugQueue.front(); lugQueue.pop();
                Event newEvent2(Event::Type::LUGGAGE, nextPassenger, nextPassenger.luggageTime);
                eventQueue.push(newEvent2);
                currentLugCounter++;
            }
            break;
        case 4:
            if(p.isVip){
                totalTime += currentTime - p.arrivalTime;
                if(currentTime > p.departureTime) numOfLatePassengers++;
            }
            else{
                if(currentSecCounter < secCounter && prioritySecQueue.empty()){
                    Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                    eventQueue.push(newEvent);
                    currentSecCounter++;
                }
                else{
                    prioritySecQueue.push(p);
                }
            }
            if(!priorityLugQueue.empty()){
                Passenger nextPassenger = priorityLugQueue.top(); priorityLugQueue.pop();
                Event newEvent2(Event::Type::LUGGAGE, nextPassenger, nextPassenger.luggageTime);
                eventQueue.push(newEvent2);
                currentLugCounter++;
            }
            break;
        case 5:
            if(currentSecCounter < secCounter && secQueue.empty()){
                Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                eventQueue.push(newEvent);
                currentSecCounter++;
            }
            else{
                secQueue.push(p);
            }
            if(!lugQueue.empty()){
                Passenger nextPassenger = lugQueue.front(); lugQueue.pop();
                Event newEvent2(Event::Type::LUGGAGE, nextPassenger, nextPassenger.luggageTime);
                eventQueue.push(newEvent2);
                currentLugCounter++;
            }
            break;
        case 2:
        case 6:
            if(currentSecCounter < secCounter && prioritySecQueue.empty()){
                Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                eventQueue.push(newEvent);
                currentSecCounter++;
            }
            else{
                prioritySecQueue.push(p);
            }
            if(!priorityLugQueue.empty()){
                Passenger nextPassenger = priorityLugQueue.top(); priorityLugQueue.pop();
                Event newEvent2(Event::Type::LUGGAGE, nextPassenger, nextPassenger.luggageTime);
                eventQueue.push(newEvent2);
                currentLugCounter++;
            }
            break;
        case 3:
        case 7:
            if(p.isVip){
                totalTime += currentTime - p.arrivalTime;
                if(currentTime > p.departureTime) numOfLatePassengers++;
            }
            else {
                if (currentSecCounter < secCounter && secQueue.empty()) {
                    Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                    eventQueue.push(newEvent);
                    currentSecCounter++;
                }
                else {
                    secQueue.push(p);
                }
            }
            if(!lugQueue.empty()){
                Passenger nextPassenger = lugQueue.front(); lugQueue.pop();
                Event newEvent2(Event::Type::LUGGAGE, nextPassenger, nextPassenger.luggageTime);
                eventQueue.push(newEvent2);
                currentLugCounter++;
            }
            break;
        case 8:
            if(p.isVip){
                totalTime += currentTime - p.arrivalTime;
                if(currentTime > p.departureTime) numOfLatePassengers++;
            }
            else {
                if (currentSecCounter < secCounter && prioritySecQueue.empty()) {
                    Event newEvent(Event::Type::SECURITY, p, p.securityTime);
                    eventQueue.push(newEvent);
                    currentSecCounter++;
                }
                else {
                    prioritySecQueue.push(p);
                }
            }
            if(!lugQueue.empty()){
                Passenger nextPassenger = priorityLugQueue.top(); priorityLugQueue.pop();
                Event newEvent2(Event::Type::LUGGAGE, nextPassenger, nextPassenger.luggageTime);
                eventQueue.push(newEvent2);
                currentLugCounter++;
            }
            break;
    }
}

void EventExecuter::executeSecurity(Event &currentEvent, int &caseNum) {
    Passenger p = currentEvent.passenger;
    totalTime += currentTime - p.arrivalTime;
    currentSecCounter--;
    if(currentTime > p.departureTime) numOfLatePassengers++;
    switch(caseNum){
        case 2:
        case 4:
        case 6:
        case 8:
            if(!prioritySecQueue.empty()){
                Passenger nextPassenger = prioritySecQueue.top(); prioritySecQueue.pop();
                Event newEvent(Event::Type::SECURITY, nextPassenger, nextPassenger.securityTime);
                eventQueue.push(newEvent);
                currentSecCounter++;
            }
            break;
        case 1:
        case 3:
        case 5:
        case 7:
            if(!secQueue.empty()){
                Passenger nextPassenger = secQueue.front(); secQueue.pop();
                Event newEvent(Event::Type::SECURITY, nextPassenger, nextPassenger.securityTime);
                eventQueue.push(newEvent);
                currentSecCounter++;
            }
            break;
    }
}


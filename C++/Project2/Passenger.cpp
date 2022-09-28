#include "Passenger.h"

Passenger::Passenger() {
    arrivalTime = 0;
    departureTime = 0;
    luggageTime = 0;
    securityTime = 0;
    isVip = false;
    hasLuggage = false;
}

Passenger::Passenger(int _arrivalTime, int _departureTime, int _luggageTime, int _securityTime, bool _isVip, bool _hasLuggage) {
    arrivalTime = _arrivalTime;
    departureTime = _departureTime;
    luggageTime = _luggageTime;
    securityTime = _securityTime;
    isVip = _isVip;
    hasLuggage = _hasLuggage;
}

Passenger::Passenger(const Passenger &passenger) {
    arrivalTime = passenger.arrivalTime;
    departureTime = passenger.departureTime;
    luggageTime = passenger.luggageTime;
    securityTime = passenger.securityTime;
    isVip = passenger.isVip;
    hasLuggage = passenger.hasLuggage;
}

Passenger& Passenger::operator=(const Passenger &passenger) {
    arrivalTime = passenger.arrivalTime;
    departureTime = passenger.departureTime;
    luggageTime = passenger.luggageTime;
    securityTime = passenger.securityTime;
    isVip = passenger.isVip;
    hasLuggage = passenger.hasLuggage;
}

Passenger::~Passenger() {

}

bool Passenger::operator < (const Passenger& other)const {
    return departureTime > other.departureTime;
}
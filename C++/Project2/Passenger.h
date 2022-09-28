#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H
class Passenger{
public:
    Passenger();
    Passenger(int _arrivalTime, int _departureTime, int _luggageTime, int _securityTime, bool _isVip, bool _hasLuggage);
    Passenger(const Passenger& passenger);
    Passenger& operator = (const Passenger& passenger);
    ~Passenger();
    bool operator < (const Passenger& other)const;
    int arrivalTime;
    int departureTime;
    int luggageTime;
    int securityTime;
    bool isVip;
    bool hasLuggage;
};



#endif //PROJECT2_PASSENGER_H

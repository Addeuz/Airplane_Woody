/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Flights.h
 * Author: andreas
 *
 * Created on den 4 oktober 2017, 14:49
 */

#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <string>
#include <vector>
#include "Passanger.h"
#include "Airplane.h"

class Flight {
private:
    int id;
protected:
    Airplane airplane; //Kanske använda sig av hela planet istället
    std::vector<Passenger> passenger;
    std::string dest;
    std::string departure;
    int time;
    std::string dep_time;
    std::string arrival_time;
    std::string date;
public:

    void calculate_time(int speed, double dist) {
        time = dist / speed;
    }

    std::string get_dest() {
        return dest;
    }

    void set_id(int flight_id) {
        id = flight_id;
    }
    void set_time(std::string reqtime){}

    bool add_passenger(Passenger p) {
        if (passenger.size() < airplane.get_max_seat()) {
            passenger.push_back(p);
            return true;
        }
        return false;
    }

    Flight(Airplane airplane, Passenger P, std::string dest, std::string departure) : airplane(airplane), dest(dest), departure(departure) {
        passenger.push_back(P);
    }
};

#endif /* FLIGHTS_H */
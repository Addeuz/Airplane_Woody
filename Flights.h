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

class Flight {
private:
    int id;
protected:
    std::string plan_id; //Kanske använda sig av hela planet istället
    std::vector<Passenger> passenger;
    std::string dest;
    std::string departure;
    int time;
public:
    void calculate_time();
    std::string get_dest(){return dest;}
    void add_passenger(Passenger p){passenger.push_back(p);}
    Flight(std::string plan_id, Passenger P, std::string dest, std::string departure) : plan_id(plan_id), dest(dest), departure(departure) {
        passenger.push_back(P);
    }
};

#endif /* FLIGHTS_H */
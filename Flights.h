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
#include "Clock.h"

class Flight {
private:
    int id;
protected:
    Airplane airplane;
    std::string departure_ICAO;
    std::string arrival_ICAO;
    std::vector<Passenger> passenger;
    std::string dest;
    std::string departure;
    std::string dep_time;
    std::string arrival_time;
    std::string date;
public:

    int get_id(){return id;}
    std::string get_dep_time(){return dep_time;}
    std::string get_arr_time(){return arrival_time;}
    std::string get_date(){return date;}
    std::string get_departure_ICAO(){return departure_ICAO;}
    std::string get_destination_ICAO(){return arrival_ICAO;}
    std::string get_dest() {return dest;}
    std::string get_dep() {return departure;}
    std::vector<Passenger> get_passenger(){return passenger;}

    int get_range() {
        return airplane.get_range();
    }

    void set_id(int flight_id) {
        id = flight_id;
    }

    void set_time(std::string date, int h, int m, double dist, int speed) {
        std::string hour = std::to_string(h), min = std::to_string(m);
        if (h < 10) {
            hour = "0" + std::to_string(h);
        }
        if (m < 10) {
            min = "0" + std::to_string(m);
        }
        dep_time = hour + ":" + min;
        Clock c;
        c.set(h, m);
        for (int i = 0; i < (dist / speed + 1)*60; i++) {
            c.tick();
        }
        hour = std::to_string(c.geth());
        min = std::to_string(c.getm());
        h = c.geth();
        m = c.getm();
        if (h < 10) {
            hour = "0" + hour;
        }
        if (m < 10) {
            min = "0" + min;
        }
        arrival_time = hour + ":" + min;


    }

    bool add_passenger(Passenger p) {
        if (passenger.size() < airplane.get_max_seat()) {
            passenger.push_back(p);
            return false;
        }
        return true;
    }

    Flight(Airplane airplane, Passenger P, std::string dest, std::string departure, std::string departure_ICAO, std::string arrival_ICAO) : airplane(airplane), dest(dest), departure(departure),departure_ICAO(departure_ICAO), arrival_ICAO(arrival_ICAO) {
        passenger.push_back(P);
    }

    int get_arrival_time() {
        return std::stoi(arrival_time.substr(0, 2));
    }

    Airplane get_airplane() {
        return airplane;
    }
    

};

#endif /* FLIGHTS_H */
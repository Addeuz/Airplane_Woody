/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Airport.h
 * Author: andreas
 *
 * Created on den 4 oktober 2017, 14:43
 */

#ifndef AIRPORT_H
#define AIRPORT_H

#include <vector>
#include <string>
#include "Airplane.h"
#include "Flights.h"
#include "Passanger.h"

class Airport {
protected:
    int ID;
    float altitude;
    double longitude;
    double latitude;
    std::vector<Airplane> airplane;
    std::vector<Flight> arrival;
    std::vector<Flight> departures;
    std::string country;
    std::string timezone;
    std::string type;
    std::string ICAO;
    std::string IATA;
    std::string city;
    std::string source;
    std::string name;
    bool no_plane;
    bool no_departure;
    bool no_arrival;
public:

    Airport(int ID, float alti, double longi, double lati, std::string coun, std::string timez, std::string typ, std::string in_ICAO, std::string in_IATA, std::string in_city, std::string in_source, std::string in_name) : ID(ID), altitude(alti), longitude(longi), latitude(lati), country(coun), timezone(timez), type(typ), ICAO(in_ICAO), IATA(in_IATA), city(in_city), source(in_source), name(in_name) {
        no_plane = true;
        no_departure = true;
        no_arrival = true;
    }
    //void set_ID();
    Flight create_flight(Airplane airplane, Passenger passenger, Airport destination, Airport departure, double dist);
    bool book_plane();

    void add_plane(Airplane plane) {
        airplane.push_back(plane);
        no_plane = false;
    }

    std::string get_ICAO() {
        return ICAO;
    }
    double get_longitude(){return longitude;}
    double get_latitude(){return latitude;}
    std::string get_name(){return name;}
    std::vector<Flight> get_departures(){return departures;}
    std::vector<Flight> get_arrivals(){return arrival;}
    void add_arrival(Flight flight){
        arrival.push_back(flight);
        no_arrival = false;
    }
    void add_departure(Flight flight){
        departures.push_back(flight);
        no_departure = false;
    }
    int get_id(){return ID;}
    std::vector<Airplane> get_airplanes(){return airplane;}
    Airplane find_plane(std::string plane_id);
    Airplane best_plane(double d);
    bool get_plane_status(){return no_plane;}
    Airplane find_arrival(std::string date, int h, int m);
    bool add(Passenger p, std::string dest);
    bool get_departure_status(){return no_departure;}
    bool get_arrival_status(){return no_arrival;}
    void remove_plane(Airplane plane);
    int get_spec_flight(std::string dest);
};

#endif /* AIRPORT_H */
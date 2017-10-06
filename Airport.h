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
    long longitude;
    long latitude;
//    int airplane;
//    int arrival;
//    int departures;
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
public:
    void set_ID();
    Airport(int ID, float alti, long longi, long lati, std::string coun, std::string timez, std::string typ, std::string in_ICAO, std::string in_IATA, std::string in_city, std::string in_source, std::string in_name);
    //Airport(int ID, int alti, int longi, int lati, int airp, int arr, int dep, std::string coun, std::string timez, std::string type, std::string ICAO, std::string IATA, std::string city, std::string source, std::string name);
    long get_longitud(Airport);
    long get_latitud(Airport);
    Flight create_flight(std::string plan_id, std::vector<Passenger> passenger, std::string destination, std::string departure, int time);
    bool book_plane();
    bool add_plane();
    void print_airport();
};

#endif /* AIRPORT_H */
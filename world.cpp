/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "World.h"
#include "Airplane.h"
#include "Airport.h"
#include "Flights.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void World::create_airplane(string file_name1, string file_name2) {
    vector<Airport>::iterator it;
    ifstream file(file_name1);
    string id, Model, Seats, Location, compare, sub;
    if (!file.is_open()) {
        cout << "No open";
    }
    getline(file, Location, '\n');
    while (getline(file, id)) {
        getline(file, id, ',');
        getline(file, Model, ',');
        getline(file, Seats, ',');
        getline(file, Location, '\n');
        Airplane obj = Airplane(Model, file_name2);
        obj.set_ID(id);
        obj.set_avail_seats(std::stoi(Seats));
        airplane.push_back(obj); //Vi lägger ännu inte till flygplan på flygpplatserna, fast de har vi väl gjort nu
        for (it = airport.begin(); it < airport.end(); it++) {
            sub = Location.substr(0, Location.size() - 1);
            compare = it->get_ICAO().substr(1, it->get_ICAO().size() - 2);

            if (compare.compare(sub) == 0) {
                it->add_plane(obj);
            }
        }
    }
}

void World::create_airport(std::string file_name) {
    ifstream file(file_name);
    string id, alti, longi, lati, country, timezone, type, ICAO, IATA, city, source, name, DST, tz;
    if (!file.is_open()) {
        cout << "No open";
    }

    while (getline(file, id)) {
        getline(file, id, ',');
        getline(file, name, ',');
        getline(file, city, ',');
        getline(file, country, ',');
        getline(file, IATA, ',');
        getline(file, ICAO, ',');
        getline(file, lati, ',');
        getline(file, longi, ',');
        getline(file, alti, ',');
        getline(file, timezone, ',');
        getline(file, DST, ',');
        getline(file, tz, ',');
        getline(file, type, ',');
        getline(file, source, '\n');
        Airport obj = Airport(stoi(id), stof(alti), stod(longi), stod(lati), country, timezone, type, ICAO, IATA, city, source, name);
        airport.push_back(obj);
    }
}

void World::create_passenger(std::string file_name) {
    vector<Airport>::iterator it1; //Location
    vector<Flight>::iterator it2;   //Flights
    vector<Airport>::iterator it3;  //Dest
    vector<Airplane>::iterator it4; //Airplane
    ifstream file(file_name);
    string id, dest, location, reqtime;
    if (!file.is_open()) {
        cout << "No open";
    }
    getline(file, id, '\n');
    while (getline(file, id)) {
        getline(file, id, ',');
        getline(file, dest, ',');
        getline(file, reqtime, ',');
        getline(file, location, '\n');
        Passenger obj = Passenger(dest, location, reqtime, stoi(id));
        passenger.push_back(obj);
        for (it1 = airport.begin(); it1 < airport.end(); it1++) {
            for (it3 = airport.begin(); it3 < airport.end(); it3++) {
                string dest_name = it3->get_ICAO().substr(1, it3->get_ICAO().size() - 2);
                if (dest == dest_name){
                    break;
                }
            }
            

            string loc_name = it1->get_ICAO().substr(1, it1->get_ICAO().size() - 2);

            if (location == loc_name) {
                bool no_flight = true;
                for (it2 = it1->departures.begin(); it2 < it1->departures.end(); it2++) {
                    string sub2 = it2->get_dest().substr(1, it2->get_dest().size() - 2);
                    if (dest == sub2) {
                        it2->add_passenger(obj);
                        no_flight = false;
                    }

                }
                if (no_flight) {
                    double d;
                    d = calculate_dist(it1->get_latitude(), it3->get_latitude() ,it1->get_longitude(), it3->get_longitude());
                    for (it4 = it1->airlane.begin(); it4 < it1->airplane.end(); it4++) {
                        
                    }
                    }
                }
            }
        }

}

double World::calculate_dist(double lat1, double lat2, double long1, double long2) {
        double r,la1,la2,lo1,lo2,d;
        r = 6371000;
        la1 = lat1 * M_PI / 180;
        la2 = lat2 * M_PI / 180;
        lo1 = long1 * M_PI / 180;
        lo2 = long2 * M_PI / 180;
        d = 2 * r * sqrt((sin((la2 - la1) / 2)^2)+(cos(la1) * cos(la2)*(sin((lo2 - lo1) / 2)^2)));
        return d;
    }



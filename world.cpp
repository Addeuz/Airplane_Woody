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
    while (getline(file, id, ','),
            getline(file, Model, ','),
            getline(file, Seats, ','),
            getline(file, Location, '\n')) {
        Airplane obj = Airplane(Model, file_name2);
        obj.set_ID(id);
        obj.set_avail_seats(std::stoi(Seats));
        airplane.push_back(obj);
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

    while (getline(file, id, ','),
            getline(file, name, ','),
            getline(file, city, ','),
            getline(file, country, ','),
            getline(file, IATA, ','),
            getline(file, ICAO, ','),
            getline(file, lati, ','),
            getline(file, longi, ','),
            getline(file, alti, ','),
            getline(file, timezone, ','),
            getline(file, DST, ','),
            getline(file, tz, ','),
            getline(file, type, ','),
            getline(file, source, '\n')) {

        Airport obj = Airport(stoi(id), stof(alti), stod(longi), stod(lati), country, timezone, type, ICAO, IATA, city, source, name);
        airport.push_back(obj);
    }
}

void World::create_passenger(std::string file_name) {
    vector<Airport>::iterator it1; //Location
    vector<Flight>::iterator it2; //Flights
    vector<Airport>::iterator it3; //Dest
    vector<Airplane>::iterator it4; //Airplane
    int plane;
    ifstream file(file_name);
    string id, dest, location, reqtime, plane_id;
    if (!file.is_open()) {
        cout << "No open";
    }
    getline(file, id, '\n');
    while (getline(file, id, ','),
        getline(file, dest, ','),
        getline(file, reqtime, ','),
        getline(file, location, '\n')) {

        Passenger obj = Passenger(dest, location, reqtime, stoi(id));
        passenger.push_back(obj);
        try {
            bool no_flight = true;
            it2 = get_airport(location).get_departures().end();
            while (it2 != get_airport(location).get_departures().end()) {
                string sub2 = it2->get_dest().substr(1, it2->get_dest().size() - 2);
                if (dest == sub2) {

                    no_flight = it2->add_passenger(obj);
                }
                it2++;
            }
            if (no_flight) {
                double d;
                d = calculate_dist(get_airport(location).get_latitude(), get_airport(dest).get_latitude(), get_airport(location).get_longitude(), get_airport(dest).get_longitude());

                if (get_airport(location).get_plane_status()) {

                } else {
                    fligths.push_back(get_airport(location).create_flight(get_airport(location).best_plane(d), obj, get_airport(dest), get_airport(location), d));

                }
            }
        } catch (const char* msg) {
            cerr << msg << endl;
        }



    }

}

double World::calculate_dist(double lat1, double lat2, double long1, double long2) {
    double r, la1, la2, lo1, lo2, d;
    r = 6371;
    la1 = lat1 * M_PI / 180;
    la2 = lat2 * M_PI / 180;
    lo1 = long1 * M_PI / 180;
    lo2 = long2 * M_PI / 180;
    d = 2 * r * sqrt((sin((la2 - la1) / 2) * sin((la2 - la1) / 2))+(cos(la1) * cos(la2)*(sin((lo2 - lo1) / 2) * sin((lo2 - lo1) / 2))));

    return d;
}

Flight Airport::create_flight(Airplane plane, Passenger passenger, Airport destination, Airport departure, double dist) {
    int i = 0;
    vector<Airplane>::iterator it;
    Flight flight(plane, passenger, destination.get_name(), departure.get_name());
    flight.set_id(passenger.get_id());
    flight.calculate_time(plane.get_max_speed(), dist);
    for (it = airplane.begin(); it < airplane.end(); it++) {
        if (it->get_id() == plane.get_id()) {
            airplane.erase(airplane.begin() + i);
        }
        i++;
    }
    flight.set_time(passenger.get_req_time());
    add_departure(flight);
    destination.add_arrival(flight);

    return flight;
}

Airplane Airport::find_plane(std::string plane_id) {
    int i = 0;
    for (vector<Airplane>::iterator it = airplane.begin(); it < airplane.end(); it++) {

        if (it->get_id() == plane_id) {

            break;
        }
        i++;

    }
    return airplane[i];
}

Airport World::get_airport(std::string ICAO) {
    int i = 0;
    bool exist = false;
    for (vector<Airport>::iterator it = airport.begin(); it < airport.end(); it++) {
        if (it->get_ICAO().substr(1, it->get_ICAO().size() - 2) == ICAO) {
            exist = true;
            break;
        }
        i++;
    }
    if (exist == false) {
        cout << ICAO << " ";
        throw "There is no airport with that name";

    }

    return airport[i];
}

Airplane Airport::best_plane(double d) {
    int range,i;
    string plane_id;
    for (vector<Airplane>::iterator it = airplane.begin(); it != airplane.end(); it++) {
        if (d < it->get_range()) {
            if (it == airplane.begin()) {
                range = it->get_range();
                i = it->get_max_seat();
                plane_id = it->get_id();
            } else if (range > it->get_range()) {
                range = it->get_range();
                plane_id = it->get_id();

            }
        }
    }
    return find_plane(plane_id);


}


//for (it1 = airport.begin(); it1 != airport.end(); it1++) {
//            it3 = airport.begin();
//
//            //for (it3 = airport.begin(); it3 != airport.end()-1; it3++) 
//            while (it3 != airport.end()) {
//                string dest_name = it3->get_ICAO().substr(1, it3->get_ICAO().size() - 2);
//                if (dest == dest_name) {
//                    cout << "FACK";
//                    break;
//                }
//                it3++;
//            }
//
//
//            string loc_name = it1->get_ICAO().substr(1, it1->get_ICAO().size() - 2);
//            //cout << loc_name << "  " << location << endl;
//            if (location == loc_name) {
//                bool no_flight = true;
//                //for (it2 = it1->get_departures().begin(); it2 != it1->get_departures().end(); it2++) 
//                it2 = it1->get_departures().begin();
//                while(it2 != it1->get_departures().end()){
//                    string sub2 = it2->get_dest().substr(1, it2->get_dest().size() - 2);
//                    if (dest == sub2) {
//                        no_flight = it2->add_passenger(obj);
//                    }
//                    it2++;
//                }
//                cout << "HEJ";
//                
//                if (no_flight) {
//                    bool no_plane = true;
//                    double d;
//                    d = calculate_dist(it1->get_latitude(), it3->get_latitude(), it1->get_longitude(), it3->get_longitude());
//                    for (it4 = it1->get_airplanes().begin(); it4 != it1->get_airplanes().end(); it4++) {
//                        if (d < it4->get_range()) {
//                            no_plane = false;
//
//                            if (it4 == it1->get_airplanes().begin()) {
//                                plane = it4->get_range();
//                                plane_id = it4->get_id();
//                            } else if (plane > it4->get_range()) {
//                                plane = it4->get_range();
//                                plane_id = it4->get_id();
//                            }
//                        }
//                    }
//                    if (no_plane) {
//
//                    }
//                    fligths.push_back(it1->create_flight(it1->find_plane(plane_id), obj, get_airport(it1->get_id()), get_airport(it3->get_id()), d));
//                }
//            }
//        }
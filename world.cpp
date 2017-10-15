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
#define _USE_MATH_DEFINES
#include <math.h>
#include "Clock.h"
#include <iomanip>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



using namespace std;



Airplane::Airplane(string Aircraft, string file_name) {
    ifstream file(file_name);
    string name, IS, passengers, range, speed, height;
    if (!file.is_open()) {
        cout << "No open";
    }
    getline(file, name, '\n');
    while (getline(file, name)) {
        getline(file, name, ',');
        if (Aircraft == name) {
            model = name;
            getline(file, IS, ',');
            getline(file, passengers, ',');
            max_seats = stoi(passengers);
            getline(file, range, ',');
            max_range = stoi(range);
            getline(file, speed, ',');
            max_speed = stoi(speed);
            getline(file, height, '\n');
            max_height = stoi(height);
        }
    }
}

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
    ifstream file(file_name);
    string id, dest, location, reqtime;
    double d;
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
            bool full_plane = true;
            int i = 0, j = 0;

            i = get_airport(location);
            j = get_airport(dest);

            d = calculate_dist(airport[i].get_latitude(), airport[j].get_latitude(), airport[i].get_longitude(), airport[j].get_longitude());

            if (airport[i].get_departure_status() == false) {
                full_plane = fligths[get_flight_place(airport[i].get_spec_flight(dest))].add_passenger(obj);
                }
                if (full_plane) {
                    if (airport[i].get_plane_status()) {
                        if (airport[i].get_arrival_status()) {
                            //BOOK PLANE
                            cout << "No plane to book" << endl;
                        } else {

                            fligths.push_back(airport[i].create_flight(airport[i].find_arrival(obj.get_req_date(), obj.get_req_time_h(), d), obj, airport[j], airport[i], d));
                            airport[i].add_departure(get_flight(stoi(id)));
                            airport[j].add_arrival(get_flight(stoi(id)));
                            airport[i].remove_plane(airport[i].find_arrival(obj.get_req_date(), obj.get_req_time_h(), d));
                        }

                    } else {
                        fligths.push_back(airport[i].create_flight(airport[i].best_plane(d), obj, airport[j], airport[i], d));
                        airport[i].add_departure(get_flight(stoi(id)));
                        airport[j].add_arrival(get_flight(stoi(id)));
                        airport[i].remove_plane(airport[i].best_plane(d));
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
        vector<Airplane>::iterator it;
        Flight flight(plane, passenger, destination.get_name(), departure.get_name(), departure.get_ICAO(), destination.get_ICAO());
        flight.set_id(passenger.get_id());
        flight.set_time(passenger.get_req_date(), passenger.get_req_time_h(), passenger.get_req_time_m(), dist, plane.get_max_speed());
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

    int World::get_airport(std::string ICAO) {
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
        return i;
    }

    Flight World::get_flight(int id) {
        int i = 0;
        bool exist = false;
        for (vector<Flight>::iterator it = fligths.begin(); it < fligths.end(); it++) {
            if (it->get_id() == id) {
                exist = true;
                break;
            }
            i++;
        }
        if (exist == false) {

            throw "There is no airport with that name";

        }

        return fligths[i];
    }

    int World::get_flight_place(int id) {
        int i = 0;
        bool exist = false;
        for (vector<Flight>::iterator it = fligths.begin(); it < fligths.end(); it++) {
            if (it->get_id() == id) {
                exist = true;
                break;
            }
            i++;
        }
        if (exist == false) {

            throw "There is no airport with that name";

        }

        return i;
    }

    Airplane Airport::best_plane(double d) {
        int range, i;
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
        if (plane_id == "") {
            throw "Inget Plan Passar";
        }
        return find_plane(plane_id);


    }

    int Clock::geth() {
        return h;
    }

    int Clock::getm() {
        return m;
    }

    void Clock::set(int hh, int mm) {
        h = hh;
        m = mm;
    }

    void Clock::tick() {
        m = (m + 1) % 60;
        if (m == 0)
            h = (h + 1) % 24;
    }

    bool Airport::add(Passenger p, string dest) {
        bool add = false;
        int i = 0;
        for (vector<Flight>::iterator it = get_departures().begin(); it != get_departures().end(); it++) {
            if (it->get_dest().size() != 4) {
                throw "Fel dest";
            }
            string sub2 = it->get_dest().substr(1, it->get_dest().size() - 2);
            cout << sub2;
            if (dest == sub2) {

                add = get_departures()[i].add_passenger(p);
                break;
            }
            i++;


        }
        return add;
    }

    int Airport::get_spec_flight(string dest) {
        int id;
        for (vector<Flight>::iterator it = departures.begin(); it != departures.end(); it++) {
            if (it->get_destination_ICAO().size() != 6) {
                throw "Fel dest";
            }
            if (dest == it->get_destination_ICAO().substr(1, 4)) {
                id = it->get_id();
                break;
            }

        }
        return id;
    }

    Airplane Airport::find_arrival(std::string date, int h, int range) {
        int i = 0;
        for (vector<Flight>::iterator it = arrival.begin(); it != arrival.end(); it++) {
            if (h > it->get_arrival_time()) {
                if (it->get_range() > range) {
                    break;
                }
                i++;
            }
        }
        return arrival[i].get_airplane();
    }

    void Airport::remove_plane(Airplane plane) {
        vector<Airplane>::iterator it;
        int i = 0;
        for (it = airplane.begin(); it < airplane.end(); it++) {
            if (it->get_id() == plane.get_id()) {
                airplane.erase(airplane.begin() + i);
            }
            i++;
        }
    }

    void World::print_csv(string file_name, string source) {
        ofstream file;
        int id;
        file.open(file_name);
        file << "Source,Flight id,Departure location,Time of departure,Arrival location,Time of arrival,Passengers id ---->,\n";
        for(int i = 0; i<fligths.size(); i++){
         int j =0;
         file <<source<<","<<fligths[i].get_id()<<","<<fligths[i].get_dep()<<","<<fligths[i].get_dep_time()<<","<<fligths[i].get_dest()<<","<<fligths[i].get_arr_time()<<",";
         for(vector<Passenger>::iterator it = fligths[i].get_passenger().begin(); it != fligths[i].get_passenger().end(); it++){   
             id = fligths[i].get_passenger()[j].get_id();
             j++;
             file << id<<",";
         }
         file << "\n";
        }
    }

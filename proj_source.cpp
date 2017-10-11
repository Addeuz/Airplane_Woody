/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Airplane.h"
#include "Airport.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//Airport::Airport(int in_ID, float alti, double longi, double lati, string coun, string timez, string typ, string in_ICAO, string in_IATA, string in_city, string in_source, string in_name) {
//    //Airport::Airport(int in_ID, int alti, int longi, int lati, int airp, int arr, int dep, string coun, string timez, string typ, string in_ICAO, string in_IATA, string in_city, string in_source, string in_name) {
//    ID = in_ID;
//    altitude = alti;
//    longitude = longi;
//    latitude = lati;
//    country = coun;
//    timezone = timez;
//    type = typ;
//    ICAO = in_ICAO;
//    IATA = in_IATA;
//    city = in_city;
//    source = in_source;
//    name = in_name;
//}


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
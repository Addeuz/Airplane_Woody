/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Airport.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

Airport::Airport(int in_ID, float alti, float longi, float lati, vector<Airplane> airp, vector<Flights> arr, vector<Flights> dep, string coun, string timez, string typ, string in_ICAO, string in_IATA, string in_city, string in_source, string in_name) {
//Airport::Airport(int in_ID, int alti, int longi, int lati, int airp, int arr, int dep, string coun, string timez, string typ, string in_ICAO, string in_IATA, string in_city, string in_source, string in_name) {
    ID = in_ID;
    altitude = alti; 
    longitude = longi;
    latitude = lati;
    airplane = airp;
    arrival = arr;
    departures = dep;
    country = coun;
    timezone = timez;
    type = typ;
    ICAO = in_ICAO;
    IATA = in_IATA;
    city = in_city;
    source = in_source;
    name = in_name;
}

long Airport::get_longitud(class Airport) {
    return (Airport.longitude);
}
long Airport::get_latitud(class Airport) {
    return (Airport.latitude);
}
//Airport::Airport(int ID, float alti, float longi, float lati, std::vector<Airplane> airp, std::vector<Flights> arr, std::vector<Flights> dep, std::string coun, std::string timez, std::string type, std::string ICAO, std::string IATA, std::string city, std::string source, std::string name) {
//ID(ID), altitude(alti), longitude(longi), airplane(airp), arrival(arr), departures(dep), country(coun), timezone(timez), type(type), ICAO(ICAO), IATA(IATA), city(city), source(source), name(name) {}

//void Airport::print_airport() {
//    cout << ID << " " << altitude << " " << longitude << " " << latitude << " " << airplane << " " << arrival << " " << departures << " " << country << " " << timezone << " " << type << " " << ICAO << " " << IATA << " " << city << " " << source << " " << name;
//}
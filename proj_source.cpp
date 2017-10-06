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
Airplane::Airplane(string Aircraft){
    
    model=Aircraft;
    if (Aircraft=="Cessna 550 Citation II")
    { 
    max_seats=8;
    max_range=3701;
    max_speed=746;
    max_height=12;
    }
     if (Aircraft=="Cessna 560 Ultra")
    {
    max_seats=7;
    max_range=3701;
    max_speed=746;
    max_height=12;
     }
     if (Aircraft=="Cessna S550 Citation SII")
    {
    max_seats=8;
    max_range=3701;
    max_speed=746;
    max_height=12;
     }
     if (Aircraft=="Hawker 800XP")
    {
    max_seats=8;
    max_range=4893;
    max_speed=745;
    max_height=11;
     }
     if (Aircraft=="Cessna 208 Caravan")
    {max_seats=9;
    max_range=1982;
    max_speed=344;
    max_height=5;
     }
     if (Aircraft=="Avro RJ85")
    {max_seats=95;
    max_range=3650;
    max_speed=747;
    max_height=10;
     }
     if (Aircraft=="Avro RJ100")
    {max_seats=112;
    max_range=3340;
    max_speed=747;
    max_height=10;
     }
     if (Aircraft=="BAe ATP")
    {max_seats=68;
    max_range=1825;
    max_speed=496;
    max_height=7;
     }
     if (Aircraft=="Saab 340A")
    {max_seats=33;
    max_range=1732;
    max_speed=467;
    max_height=7;
     }
     if (Aircraft=="Saab 340B")
    {max_seats=33;
    max_range=1732;
    max_speed=467;
    max_height=7;
     }
     if (Aircraft=="Airbus A320-200")
    {max_seats=180;
    max_range=6100;
    max_speed=829;
    max_height=10;
     }
     if (Aircraft=="Airbus A321neo")
    {max_seats=221;
    max_range=6500;
    max_speed=833;
    max_height=10;
     }
    


}
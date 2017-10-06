/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "World.h"
#include "Airplane.h"
#include "Airport.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

void World::create_airplane(string file_name){

ifstream file ( file_name); 
string id,Model,Seats,Location;
if(!file.is_open()){
    cout << "No open";
}
getline ( file, Location, '\n' );
while ( file.good() )
{
    getline ( file, id, ',' );
    getline ( file, Model, ',' );
    getline ( file, Seats, ',' );
    getline ( file, Location, '\n' );
    Airplane obj = Airplane(Model);
    obj.set_ID(id);
    obj.set_avail_seats(std::stoi(Seats));
    //World.airplane.push_back(obj); //Vi lägger ännu inte till flygplan på flygpplatserna
}
}

void World::create_airport(std::string file_name){

ifstream file ( file_name); 
string id, alti, longi , lati, country, timezone, type, ICAO, IATA, city, source, name, DST, tz;
if(!file.is_open()){
    cout << "No open";
}

while ( file.good() )
{
    getline ( file, id, ',' );
    getline ( file, name, ',' );
    getline ( file, city, ',' );
    getline ( file, country, ',' );
    getline ( file, IATA, ',' );
    getline ( file, ICAO, ',' );
    getline ( file, lati, ',' );
    getline ( file, longi, ',' );
    getline ( file, alti, ',' );
    getline ( file, timezone, ',' );
    getline ( file, DST, ',' );
    getline ( file, tz, ',' );
    getline ( file, type, ',' );
    getline ( file, source, '\n' );
    Airport obj = Airport(stoi(id), stof(alti), stol(longi), stol(lati), country, timezone, type, ICAO, IATA, city, source, name);
    //World.airport.push_back(obj);
}
    
}

void World::create_passenger(std::string file_name){

ifstream file ( file_name); 
string id, dest, location, reqtime;
if(!file.is_open()){
    cout << "No open";
}
getline(file, id, '\n');
while ( file.good() )
{
    getline ( file, id, ',' );
    getline ( file, dest, ',' );
    getline ( file, reqtime, ',' );
    getline ( file, location, '\n' );
    Passenger obj = Passenger(dest, location, reqtime, stoi(id)); 
    //World.passeger.push_back(obj);
    //World.airport.search(.name) Här ska fligth hittas och skapas osv....
    //dest              i.getname
            
}
    
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andreas
 *
 * Created on den 4 oktober 2017, 14:32
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Airport.h"
#include "Airplane.h"
#include "Passanger.h"
#include "World.h"
#include "Flights.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    World w;
    w.create_airport("airport.csv");
    w.create_airplane("fleet.csv", "craftinfo.csv");
    w.create_passenger("flight.csv");
    
    
    return 0;
    
}


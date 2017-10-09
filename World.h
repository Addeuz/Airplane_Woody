/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   World.h
 * Author: karl9
 *
 * Created on den 4 oktober 2017, 16:27
 */

#ifndef WORLD_H
#define WORLD_H
#include "Airplane.h"
#include "Passanger.h"
#include "Airport.h"
#include <vector>
#include <string>

class World {
protected:
    std::vector<Airplane> airplane;
    std::vector<Passenger> passenger;
    std::vector<Airport> airport;
public:
    void create_airplane(std::string file_name);
    void create_airport(std::string file_name);
    void create_passenger(std::string file_name);


};



#endif /* WORLD_H */


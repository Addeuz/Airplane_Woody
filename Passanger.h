/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Passanger.h
 * Author: andreas
 *
 * Created on den 4 oktober 2017, 15:01
 */

#ifndef PASSANGER_H
#define PASSANGER_H
#include <string>

class Passenger{
private:
    int ID;
protected:
    std::string dest;
    std:: string location;
    std:: string req_time;
public:
    Passenger(std::string dest, std::string location, std::string req_time, int ID): dest(dest), location(location), req_time(req_time), ID(ID) {}      
    

};

#endif /* PASSANGER_H */


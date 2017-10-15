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

class Passenger {
protected:
    int ID;
    std::string dest;
    std::string location;
    std::string req_time;
    int req_time_h;
    std::string req_date;
    int req_time_m;
public:

    Passenger(std::string dest, std::string location, std::string req_time, int ID) : dest(dest), location(location), req_time(req_time), ID(ID) {
        set_time();
    }
    int get_id(){return ID;}
    int get_req_time_h(){return req_time_h;}
    int get_req_time_m(){return req_time_m;}
    std::string get_req_date(){return req_date;}
    void set_time(){
        req_date= req_time.substr(0,10);
        req_time_h= std::stoi(req_time.substr(11,2)) + std::stoi(req_time.substr(17,2));
        req_time_m= std::stoi(req_time.substr(14,2));
    }
};

#endif /* PASSANGER_H */
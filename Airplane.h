/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Airplane.h
 * Author: andreas
 *
 * Created on den 4 oktober 2017, 14:48
 */

#ifndef AIRPLANE_H
#define AIRPLANE_H
#include <string>

class Airplane {
private:
    std::string ID;

protected:
    std::string model;
    int avail_seats;
    int max_seats;
    int max_range;
    int max_speed;
    int max_height;
public:

    void set_ID(std::string id) {
        ID = id;
    }
    void set_model();

    void set_avail_seats(int x) {
        avail_seats = x;
    }
    Airplane(std::string Aircraft);

    std::string get_model() {
        return model;
    }

};


#endif /* AIRPLANE_H */


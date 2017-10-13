/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clock.h
 * Author: vidhoh161
 *
 * Created on October 13, 2017, 10:00 AM
 */

#ifndef CLOCK_H
#define CLOCK_H


class Clock {
private:
	int h, m, s;
public:
	int geth();
	int getm();
	void tick();
	void set(int hh, int mm);
};


#endif /* CLOCK_H */



/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Steane.h
 * Author: attila
 *
 * Created on September 23, 2017, 4:10 PM
 */

#ifndef STEANE_H
#define STEANE_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;
using namespace std;

class Steane : public Code {
public:
    static const int CS;

    Steane(bool b, int errt) : Code(b, errt) {
    }
    bool run();
    string getDescriptor();
protected:
    void encode(bool b);

    unsigned getCS() {
        return Steane::CS;
    }
    void testError();
private:
    bool xflip[3];
    bool zflip[3];
    void errorCorrection(bool *a);
    void decode();
};

#endif /* STEANE_H */


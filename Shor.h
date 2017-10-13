/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shor.h
 * Author: attila
 *
 * Created on September 23, 2017, 2:13 PM
 */

#ifndef SHOR_H
#define SHOR_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;
using namespace std;

class Shor : public Code {
public:
    static const unsigned CS;
    typedef Code super;

    Shor(bool b, int errt) : Code(b, errt) {
    }
    bool run();
    string getDescriptor();
protected:
    void testError();
    void encode(bool b);

    unsigned getCS() {
        return Shor::CS;
    }
private:
    bool xflip[6];
    bool zflip[2];
    void errorCorrection(bool *a,
            const vector<unsigned> &b);
    void decode();
};

#endif /* SHOR_H */


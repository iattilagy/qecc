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

    Steane(bool b) : Code(b) {
    }
    bool run() override;
    string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return Steane::CS;
    }
private:
    bool xflip[3];
    bool zflip[3];
    void errorCorrection(bool *a);
    void decode();
};

#endif /* STEANE_H */


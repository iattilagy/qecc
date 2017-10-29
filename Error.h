/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Error.h
 * Author: attila
 *
 * Created on October 13, 2017, 1:31 PM
 */

#ifndef ERROR_H
#define ERROR_H

#include "qpp.h"
using namespace qpp;

class Code;

class Error {
private:
    int errorType;
    //For random error this these mean likeliness in per mille
    //For const any non zero number will trigger an error 
    unsigned x = 0;
    unsigned y = 0;
    unsigned z = 0;
    double adcg = 0;
    unsigned bit;
    bool all;
public:
    static const int CONST;
    static const int RAND;
    static const int ADC;
    //bit==codesize means all bits

    Error(int errt) {
        this->all = true;
        this->errorType = errt;
    }

    Error(unsigned bit, int errt) {
        this->bit = bit;
        this->all = false;
        this->errorType = errt;
    }
    void runError(Code *code);
    void runErrorOneBit(Code *code, unsigned index);

    void setError(unsigned x, unsigned y, unsigned z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    std::string getError() {
        std::ostringstream de;
        de << x << " " << y << " " << z;
        return de.str();
    }

    void setError(double adcg) {
        this->adcg = adcg;
    }
};

#endif /* ERROR_H */


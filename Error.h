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

class Error {
private:
    int errorType;
    //For random error this these mean likeliness in per mille
    //For const any non zero number will trigger an error 
    unsigned x = 0;
    unsigned y = 0;
    unsigned z = 0;
    unsigned bit;
    unsigned codesize;
public:
    static const int CONST;
    static const int RAND;
    //bit==codesize means all bits

    Error(unsigned codesize, int errt) {
        this->bit = codesize;
        this->codesize = codesize;
        this->errorType = errt;
    }

    Error(unsigned bit, unsigned codesize, int errt) {
        this->bit = bit;
        this->codesize = codesize;
        this->errorType = errt;
    }
    void runError(ket &c, cmat &d, bool &m);
    void runErrorOneBit(ket &c, cmat &d, bool &m, unsigned index);

    void setError(unsigned x, unsigned y, unsigned z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif /* ERROR_H */


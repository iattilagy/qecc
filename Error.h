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
using namespace std;

class Error {
private:
    int errorType;
    //For random error this these mean likeliness in per mille
    //For const any non zero number will trigger an error 
    unsigned x;
    unsigned y;
    unsigned z;
    unsigned bit;
    unsigned codesize;
public:
    static const int CONST;
    static const int RAND;
    //bit==codesize means all bits

    Error(unsigned bit, unsigned codesize, int errt) {
        this->bit = bit;
        this->codesize = codesize;
        this->errorType = errt;
    }
    runError(ket c);
    runErrorOneBit(ket c, unsigned index);
};

#endif /* ERROR_H */


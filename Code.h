/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Code.h
 * Author: attila
 *
 * Created on September 23, 2017, 4:19 PM
 */

#ifndef CODE_H
#define CODE_H

#include "qpp.h"
#include <iostream>

using namespace qpp;
using namespace std;

class Code {
public:
    static const int TEST;
    static const int RAND;

    Code(bool b, int errt);

    virtual bool run() = 0;

    void setTestErr(unsigned id) {
        testErrorId = id;
    }

    void setRandErr(int x, int y, int z) {
        randX = x;
        randY = y;
        randZ = z;
    }

    bool getOK() {
        return ok;
    }
    virtual string getDescriptor() = 0;
protected:
    ket c;
    int errorType;
    unsigned testErrorId;
    int randX;
    int randY;
    int randZ;
    bool input;
    bool result;
    bool ok;
    bool setandmesAnc(const vector<unsigned> &b, unsigned anc);
    void hadamardAllCodeBits();
    void hadamardCodeBits(const vector<unsigned> &b);
    bool getMes(unsigned i);

    void error() {
        if (errorType == TEST)
            testError();
        else if (errorType == RAND)
            randError();

        //Default to no error              
    }
    virtual void testError() = 0;
    virtual void randError();
    virtual void encode(bool b) = 0;
    virtual unsigned getCS() = 0;
};

#endif /* CODE_H */


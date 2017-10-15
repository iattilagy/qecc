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
#include "Error.h"
#include <iostream>
#include <queue>
#include <atomic>

using namespace qpp;
using namespace std;

class Code {
public:
    static const int TEST;
    static const int RAND;

    Code(bool b);
    atomic_int *errorCounter;
    atomic_int *threadCounter;

    virtual bool run() = 0;

    void addError(Error *e) {
        errorlist.push(e);
    }

    bool getOK() {
        return ok;
    }
    virtual string getDescriptor() = 0;
protected:
    ket c;
    queue<Error *> errorlist;
    bool input;
    bool result;
    bool ok;
    bool setandmesAnc(const vector<unsigned> &b, unsigned anc);
    void hadamardAllCodeBits();
    void hadamardCodeBits(const vector<unsigned> &b);
    bool getMes(unsigned i);

    void error() {
        while (!errorlist.empty()) {
            Error *e = errorlist.front();
            e->runError(c);
            delete e;
            errorlist.pop();
        }
    }
    virtual void encode(bool b) = 0;
    virtual unsigned getCS() = 0;
};

#endif /* CODE_H */


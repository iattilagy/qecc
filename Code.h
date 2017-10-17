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

class Code {
public:
    static const int TEST;
    static const int RAND;

    Code(bool b);
    std::atomic_int *errorCounter;
    std::atomic_int *threadCounter;

    virtual bool run() = 0;

    void addError(Error *e) {
        errorlist.push(e);
    }

    bool getOK() {
        return ok;
    }
    virtual std::string getDescriptor() = 0;

    void disableErrorDeletion() {
        deleteError = false;
    }
protected:
    ket c;
    std::queue<Error *> errorlist;
    bool input;
    bool deleteError;
    bool result;
    bool ok;
    bool setandmesAnc(const std::vector<unsigned> &b, unsigned anc);
    void hadamardAllCodeBits();
    void hadamardCodeBits(const std::vector<unsigned> &b);
    bool getMes(unsigned i);

    void error();
    virtual void encode(bool b) = 0;
    virtual unsigned getCS() = 0;
};

#endif /* CODE_H */


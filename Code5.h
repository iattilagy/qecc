/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Code5.h
 * Author: attila
 *
 * Created on September 24, 2017, 2:40 PM
 */

#ifndef CODE5_H
#define CODE5_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;
using namespace std;

class Code5 : public Code {
public:
    static const unsigned CS;

    Code5(bool b) : Code(b) {

    }
    bool run() override;
    string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return Code5::CS;
    }
    void testError();
private:
    bool flip[4];
    void errorCorrection(bool *a);
    void decode();
};

#endif /* CODE5_H */


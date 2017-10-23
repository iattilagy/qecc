/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Error.cpp
 * Author: attila
 * 
 * Created on October 13, 2017, 1:31 PM
 */

#include "Error.h"

const int Error::CONST = 42;
const int Error::RAND = 43;

void Error::runError(ket &c, cmat &d, bool &m) {
    if (bit < codesize) {
        runErrorOneBit(c, d, m, bit);
    } else if (bit == codesize) {
        for (unsigned i = 0; i < codesize; i++) {
            runErrorOneBit(c, d, m, i);
        }
    } else {
        throw std::string("class Error: bit cannot be more than codesize!!!");
    }
}

void Error::runErrorOneBit(ket &c, cmat &d, bool &m, unsigned index) {
    if (!m) {
        if (errorType == Error::RAND) {
            if (abs(rand()) % 1000 < x)
                c = apply(c, gt.X,{index});
            if (abs(rand()) % 1000 < y)
                c = apply(c, gt.Z,{index});
            if (abs(rand()) % 1000 < z)
                c = apply(c, gt.Y,{index});
        } else if (errorType == Error::CONST) {
            if (x)
                c = apply(c, gt.X,{index});
            if (y)
                c = apply(c, gt.Y,{index});
            if (z)
                c = apply(c, gt.Z,{index});
        }
    } else {
        if (errorType == Error::RAND) {
            if (abs(rand()) % 1000 < x)
                d = apply(d, gt.X,{index});
            if (abs(rand()) % 1000 < y)
                d = apply(d, gt.Z,{index});
            if (abs(rand()) % 1000 < z)
                d = apply(d, gt.Y,{index});
        } else if (errorType == Error::CONST) {
            if (x)
                d = apply(d, gt.X,{index});
            if (y)
                d = apply(d, gt.Y,{index});
            if (z)
                d = apply(d, gt.Z,{index});
        }
    }
}
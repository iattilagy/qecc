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
#include "Code.h"

const int Error::CONST = 42;
const int Error::RAND = 43;
const int Error::ADC = 44;

void Error::runError(Code *code) {
    if (errorType == Error::CONST || errorType == Error::RAND) {
        if (!all) {
            runErrorOneBit(code, bit);
        } else {
            for (unsigned i = 0; i < code->getCS(); i++) {
                runErrorOneBit(code, i);
            }
        }
    } else if (errorType == Error::ADC) {
        std::vector<cmat> channel;
        cmat E0, E1;
        E0.resize(2, 2);
        E1.resize(2, 2);
        E0 << 1, 0, 0, sqrt(1 - adcg);
        E1 << 0, sqrt(adcg), 0, 0;
        channel.push_back(E0);
        channel.push_back(E1);
        if (!code->mixed)
            code->convertToMixed();

        for (idx i = 0; i < code->getCS(); i++) {
            *code->d = apply(*code->d, channel, {
                i
            });
        }
    }
}

void Error::runErrorOneBit(Code *code, unsigned index) {
    if (errorType == Error::RAND) {
        if (abs(rand()) % 1000 < x)
            code->applyGT(gt.X, index);
        if (abs(rand()) % 1000 < y)
            code->applyGT(gt.Y, index);
        if (abs(rand()) % 1000 < z)
            code->applyGT(gt.Z, index);
    } else if (errorType == Error::CONST) {
        if (x)
            code->applyGT(gt.X, index);
        if (y)
            code->applyGT(gt.Y, index);
        if (z)
            code->applyGT(gt.Z, index);
    }
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BitFlip.h
 * Author: attila
 *
 * Created on October 23, 2017, 4:07 PM
 */

#ifndef BITFLIP_H
#define BITFLIP_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;

class BitFlip : public Code {
public:
    static const unsigned CS;

    BitFlip(bool b) : Code(b) {

    }
    bool run() override;
    std::string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return BitFlip::CS;
    }
    void testError();
private:
    bool flip[2];
    void errorCorrection();
    void decode();
};

#endif /* BITFLIP_H */


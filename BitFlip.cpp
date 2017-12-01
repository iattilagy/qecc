/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BitFlip.cpp
 * Author: attila
 * 
 * Created on October 23, 2017, 4:07 PM
 */

#include "BitFlip.h"

const unsigned BitFlip::CS = 3;

std::string BitFlip::getDescriptor() {
    std::ostringstream de;
    de << "BITFLIP\t";
    de << flip[0] << flip[1] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void BitFlip::encode(bool b) {
    *c = mket({b ? 1u : 0u, 0, 0});
    if (mixed) {
        convertToMixed();
    }
    if (plusminus) {
        applyGT(gt.H, 0);
    }

    applyCGT(gt.CNOT,{0, 1});
    applyCGT(gt.CNOT,{0, 2});
}

void BitFlip::decode() {
    applyCGT(gt.CNOT,{0, 2});
    applyCGT(gt.CNOT,{0, 1});
}

void BitFlip::errorCorrection() {
    if (flip[0] && flip[1])
        applyGT(gt.X, 0);
    else if (flip[0] && !flip[1])
        applyGT(gt.X, 1);
    else if (!flip[0] && flip[1])
        applyGT(gt.X, 2);
}

bool BitFlip::run() {
    encode(input);

    error();

    flip[0] = setandmesAnc({0, 1, CS}, CS);
    flip[1] = setandmesAnc({0, 2, CS}, CS);

    errorCorrection();

    decode();

    if (plusminus) {
        applyGT(gt.H, 0);
    }
    result = getMes(0);
    ok = (result == input);
    return result;
}
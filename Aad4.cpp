/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Aad4.cpp
 * Author: attila
 * 
 * Created on October 23, 2017, 3:03 PM
 */

#include "Aad4.h"
#include <complex>
#include <math.h>

const unsigned Aad4::CS = 4;

std::string Aad4::getDescriptor() {
    std::ostringstream de;
    de << "ADCODE4\t";
    de << flip[0] << flip[1] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void Aad4::encode(bool b) {
    *c = mket({0, 0, b ? 1u : 0u, 0});
    if (mixed) {
        convertToMixed();
    }

    applyCGT(gt.CNOT,{2, 3});
    cmat rot;
    rot.resize(2, 2);
    std::complex<double> mi(0, -1);
    rot << 1, 0, 0, exp(mi * M_PI / 4.);
    applyGT(rot, 0);
    applyCGT(gt.CNOT,{0, 1});
    applyCGT(gt.CNOT,{0, 2});
    applyCGT(gt.CNOT,{0, 3});
}

bool Aad4::run() {
    encode(input);

    error();

    applyCGT(gt.CNOT,{0, 1});
    applyCGT(gt.CNOT,{2, 3});

    flip[0] = getMes(1);
    flip[1] = getMes(3);

    if (!flip[0] && !flip[1]) {
        applyCGT(gt.CNOT,{2, 0});
        result = getMes(0);
    } else if (flip[0] && !flip[1]) {
        applyGT(gt.X, 2);
        result = getMes(2);
    } else if (!flip[0] && flip[1]) {
        applyGT(gt.X, 0);
        result = getMes(0);
    }

    ok = (result == input);
    return result;
}

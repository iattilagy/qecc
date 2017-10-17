/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Steane.cpp
 * Author: attila
 * 
 * Created on September 23, 2017, 4:10 PM
 */

#include "Steane.h"

const int Steane::CS = 7;

std::string Steane::getDescriptor() {
    std::ostringstream de;
    de << "STEANE\t";
    de << xflip[0] << xflip[1] << xflip [2] << "\t";
    de << zflip[0] << zflip[1] << zflip [2] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void Steane::encode(bool b) {
    if (b)
        c = mket({0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    else
        c = mket({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    c = apply(c, gt.H,{0});
    c = apply(c, gt.H,{1});
    c = apply(c, gt.H,{2});

    c = apply(c, gt.CNOT,{3, 4});
    c = apply(c, gt.CNOT,{3, 5});

    c = apply(c, gt.CNOT,{1, 3});
    c = apply(c, gt.CNOT,{1, 5});
    c = apply(c, gt.CNOT,{1, 6});

    c = apply(c, gt.CNOT,{2, 3});
    c = apply(c, gt.CNOT,{2, 4});
    c = apply(c, gt.CNOT,{2, 6});

    c = apply(c, gt.CNOT,{0, 4});
    c = apply(c, gt.CNOT,{0, 5});
    c = apply(c, gt.CNOT,{0, 6});
}

void Steane::decode() {
    c = apply(c, gt.CNOT,{0, 4});
    c = apply(c, gt.CNOT,{0, 5});
    c = apply(c, gt.CNOT,{0, 6});

    c = apply(c, gt.CNOT,{1, 3});
    c = apply(c, gt.CNOT,{1, 5});
    c = apply(c, gt.CNOT,{1, 6});

    c = apply(c, gt.CNOT,{2, 3});
    c = apply(c, gt.CNOT,{2, 4});
    c = apply(c, gt.CNOT,{2, 6});

    c = apply(c, gt.CNOT,{3, 4});
    c = apply(c, gt.CNOT,{3, 5});

    c = apply(c, gt.H,{0});
    c = apply(c, gt.H,{1});
    c = apply(c, gt.H,{2});
}

void Steane::errorCorrection(bool *a) {
    switch (a[0]*4 + a[1] *2 + a[2]) {
        case 4:
            c = apply(c, gt.X,{0});
            break;
        case 2:
            c = apply(c, gt.X,{1});
            break;
        case 1:
            c = apply(c, gt.X,{2});
            break;
        case 3:
            c = apply(c, gt.X,{3});
            break;
        case 5:
            c = apply(c, gt.X,{4});
            break;
        case 6:
            c = apply(c, gt.X,{5});
            break;
        case 7:
            c = apply(c, gt.X,{6});
            break;
    }
}

bool Steane::run() {
    encode(input);

    error();

    xflip [0] = setandmesAnc({0, 4, 5, 6}, 7);
    xflip [1] = setandmesAnc({1, 3, 5, 6}, 8);
    xflip [2] = setandmesAnc({2, 3, 4, 6}, 9);
    errorCorrection(xflip);

    hadamardAllCodeBits();
    zflip [0] = setandmesAnc({0, 4, 5, 6}, 10);
    zflip [1] = setandmesAnc({1, 3, 5, 6}, 11);
    zflip [2] = setandmesAnc({2, 3, 4, 6}, 12);
    errorCorrection(zflip);
    hadamardAllCodeBits();

    decode();
    result = getMes(3);
    ok = (result == input);
    return result;
}
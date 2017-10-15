/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Code5.cpp
 * Author: attila
 * 
 * Created on September 24, 2017, 2:40 PM
 */

#include "Code5.h"

const unsigned Code5::CS = 5;

string Code5::getDescriptor() {
    ostringstream de;
    de << "5QUBIT\t";
    de << flip[0] << flip[1] << flip [2] << flip[4] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << endl;
    return de.str();
}

void Code5::encode(bool b) {
    if (input)
        c = mket({1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    else
        c = mket({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    c = apply(c, gt.H,{1});
    c = apply(c, gt.H,{2});
    c = apply(c, gt.H,{3});
    c = apply(c, gt.H,{4});

    c = apply(c, gt.CNOT,{4, 0});
    c = apply(c, gt.CNOT,{3, 0});
    c = apply(c, gt.CNOT,{2, 0});
    c = apply(c, gt.CNOT,{1, 0});

    c = apply(c, gt.CZ,{4, 3});
    c = apply(c, gt.CZ,{3, 2});
    c = apply(c, gt.CZ,{2, 1});
    c = apply(c, gt.CZ,{1, 0});
    c = apply(c, gt.CZ,{0, 4});
}

void Code5::decode() {
    c = apply(c, gt.CZ,{0, 4});
    c = apply(c, gt.CZ,{1, 0});
    c = apply(c, gt.CZ,{2, 1});
    c = apply(c, gt.CZ,{3, 2});
    c = apply(c, gt.CZ,{4, 3});

    c = apply(c, gt.CNOT,{1, 0});
    c = apply(c, gt.CNOT,{2, 0});
    c = apply(c, gt.CNOT,{3, 0});
    c = apply(c, gt.CNOT,{4, 0});

    c = apply(c, gt.H,{1});
    c = apply(c, gt.H,{2});
    c = apply(c, gt.H,{3});
    c = apply(c, gt.H,{4});
}

void Code5::errorCorrection(bool* a) {
    unsigned char ec = 0;
    ec += flip[0];
    ec <<= 1;
    ec += flip[1];
    ec <<= 1;
    ec += flip[2];
    ec <<= 1;
    ec += flip[3];

    switch (ec) {
        case 1:
            c = apply(c, gt.X,{0});
            break;
        case 2:
            c = apply(c, gt.Z,{2});
            break;
        case 3:
            c = apply(c, gt.X,{4});
            break;
        case 4:
            c = apply(c, gt.Z,{4});
            break;
        case 5:
            c = apply(c, gt.Z,{1});
            break;
        case 6:
            c = apply(c, gt.X,{3});
            break;
        case 7:
            c = apply(c, gt.X,{4});
            c = apply(c, gt.Z,{4});
            break;
        case 8:
            c = apply(c, gt.X,{1});
            break;
        case 9:
            c = apply(c, gt.Z,{3});
            break;
        case 10:
            c = apply(c, gt.Z,{0});
            break;
        case 11:
            c = apply(c, gt.X,{0});
            c = apply(c, gt.Z,{0});
            break;
        case 12:
            c = apply(c, gt.X,{2});
            break;
        case 13:
            c = apply(c, gt.X,{1});
            c = apply(c, gt.Z,{1});
            break;
        case 14:
            c = apply(c, gt.X,{2});
            c = apply(c, gt.Z,{2});
            break;
        case 15:
            c = apply(c, gt.X,{3});
            c = apply(c, gt.Z,{3});
            break;
    }
}

bool Code5::run() {
    encode(input);

    error();

    hadamardCodeBits({0, 3, CS});
    flip[0] = setandmesAnc({0, 1, 2, 3, CS}, 6);
    hadamardCodeBits({0, 3, CS});

    hadamardCodeBits({1, 4, CS});
    flip[1] = setandmesAnc({1, 2, 3, 4, CS}, 7);
    hadamardCodeBits({1, 4, CS});

    hadamardCodeBits({0, 2, CS});
    flip[2] = setandmesAnc({0, 2, 3, 4, CS}, 8);
    hadamardCodeBits({0, 2, CS});

    hadamardCodeBits({1, 3, CS});
    flip[3] = setandmesAnc({0, 1, 3, 4, CS}, 9);
    hadamardCodeBits({1, 3, CS});

    errorCorrection(flip);

    decode();
    result = getMes(0);
    ok = (result == input);
    return result;
}
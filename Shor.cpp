/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shor.cpp
 * Author: attila
 * 
 * Created on September 23, 2017, 2:13 PM
 */

#include "Shor.h"

const unsigned Shor::CS = 9;

void Shor::encode(bool b) {
    *c = codes.codeword(Codes::Type::NINE_QUBIT_SHOR, b);
    if (mixed) {
        convertToMixed();
    }
}

std::string Shor::getDescriptor() {
    std::ostringstream de;
    de << "SHOR\t";
    for (int i = 0; i < 6; i++) {
        de << xflip[i];
    }
    de << "\t";
    de << zflip[0];
    de << zflip[1] << "\t";

    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void Shor::decode() {
    applyCGT(gt.CNOT,{0, 1});
    applyCGT(gt.CNOT,{0, 2});
    applyCGT(gt.CNOT,{3, 4});
    applyCGT(gt.CNOT,{3, 5});
    applyCGT(gt.CNOT,{6, 7});
    applyCGT(gt.CNOT,{6, 8});

    applyGT(gt.H, 0);
    applyGT(gt.H, 3);
    applyGT(gt.H, 6);

    applyCGT(gt.CNOT,{0, 3});
    applyCGT(gt.CNOT,{0, 6});
}

void Shor::errorCorrection(bool *a, const std::vector<unsigned> &b) {
    if (a[0] && a[1])
        applyGT(gt.X, b[0]);
    else if (a[0] && !a[1])
        applyGT(gt.X, b[1]);
    else if (!a[0] && a[1])
        applyGT(gt.X, b[2]);
}

//Test errors should NOT cause bit flip

bool Shor::run() {
    encode(input);

    error();

    //X error correction
    xflip[0] = setandmesAnc({0, 1, CS}, CS);
    xflip[1] = setandmesAnc({0, 2, CS}, CS);
    xflip[2] = setandmesAnc({3, 4, CS}, CS);
    xflip[3] = setandmesAnc({3, 5, CS}, CS);
    xflip[4] = setandmesAnc({6, 7, CS}, CS);
    xflip[5] = setandmesAnc({6, 8, CS}, CS);

    //errorCorrection's 1st arg is a bool array
    //with 2 bools!!!
    errorCorrection(&xflip[0],{0, 1, 2});
    errorCorrection(&xflip[2],{3, 4, 5});
    errorCorrection(&xflip[4],{6, 7, 8});

    //Z error correction
    hadamardAllCodeBits();
    zflip[0] = setandmesAnc({0, 1, 2, 3, 4, 5, CS}, CS);
    zflip[1] = setandmesAnc({0, 1, 2, 6, 7, 8, CS}, CS);
    errorCorrection(zflip,{0, 3, 6});
    hadamardAllCodeBits();

    decode();
    result = getMes(0);
    ok = (result == input);
    return result;
}
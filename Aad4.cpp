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

using namespace std;

std::string Aad4::getDescriptor() {
    std::ostringstream de;
    de << "ADCODE4\t";
    de << flip[0] << flip[1] << " " << flip[2] << flip[3] << " " << flip[4] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void Aad4::encode(bool b) {
    *c = mket({0, 0, 0, b ? 1u : 0u});

    if (plusminus) {
        applyGT(gt.H, 3);
    }

    //applyGT(gt.H, 3);

    //This code is forced to be mixed
    convertToMixed();

    applyCGT(gt.CNOT,{3, 2});
    applyGT(gt.H, 0);
    applyCGT(gt.CNOT,{0, 1});
    applyCGT(gt.CNOT,{0, 2});
    applyCGT(gt.CNOT,{0, 3});
}

void Aad4::decode() {
    applyCGT(gt.CNOT,{0, 3});
    applyCGT(gt.CNOT,{0, 2});
    applyCGT(gt.CNOT,{0, 1});
    applyGT(gt.H, 0);
    applyCGT(gt.CNOT,{3, 2});
}

bool Aad4::run() {
    encode(input);

    error();


    flip[2] = 0;
    flip[3] = 0;
    flip[4] = 0;


    bool *tf = setandmes2Anc();
    flip[0] = tf[0];
    flip[1] = tf[1];
    flip[2] = tf[2];
    flip[3] = tf[3];

    if (flip[0] || flip[1]) {
        errorOp(flip);
    } else {
        flip[4] = noErrorOp();
    }

    decode();

    if (plusminus) {
        applyGT(gt.H, 3);
    }

    //applyGT(gt.H, 3);
    result = getMes(3);
    ok = (result == input);
    return result;
}

bool Aad4::noErrorOp() {
    *d = kron(*d, mket({0}) * mket({0}).adjoint());

    applyGT(gt.H, CS);
    for (unsigned i = 0; i < CS; i++) {
        applyCGT(gt.CNOT,{CS, i});
    }
    applyGT(gt.H, CS);

    bool m = getMes(CS);
    *d = ptrace(*d,{CS});

    //Correct phase error if we have one
    if (m) {
        for (unsigned i = 0; i < CS; i++) {
            applyGT(gt.Z, i);
        }
    }

    return m;
}

bool *Aad4::setandmes2Anc() {
    bool *f = new bool[2];

    *d = kron(*d, mket({0, 0, 0, 0}) * mket({0, 0, 0, 0}).adjoint());

    applyCGT(gt.CNOT,{0, Aad4::CS});
    applyCGT(gt.CNOT,{1, Aad4::CS});
    f[0] = getMes(Aad4::CS);

    f[2] = 0;
    if (f[0]) {
        applyCGT(gt.CNOT,{0, Aad4::CS + 1});
        f[2] = getMes(Aad4::CS + 1);
    }

    applyCGT(gt.CNOT,{2, Aad4::CS + 2});
    applyCGT(gt.CNOT,{3, Aad4::CS + 2});
    f[1] = getMes(Aad4::CS + 2);

    f[3] = 0;
    if (f[1]) {
        applyCGT(gt.CNOT,{2, Aad4::CS + 3});
        f[3] = getMes(Aad4::CS + 3);
    }

    *d = ptrace(*d,{Aad4::CS + 3});
    *d = ptrace(*d,{Aad4::CS + 2});
    *d = ptrace(*d,{Aad4::CS + 1});
    *d = ptrace(*d,{Aad4::CS});
    return f;
}

bool Aad4::errorOp(bool * f) {
    unsigned h;

    if (f[0] && f[2]) h = 0;
    else if (f[0] && !f[2]) h = 1;
    else if (f[1] && f[3]) h = 2;
    else if (f[1] && !f[3]) h = 3;
    else return false;

    applyGT(gt.H, h);

    for (unsigned i = 0; i < Aad4::CS - 1; i++) {
        if (i != h)
            applyCGT(gt.CNOT,{h, i});
    }


    if (f[0] && f[2]) applyGT(gt.X, 0);
    if (f[0] && !f[2]) applyGT(gt.X, 1);
    if (f[1] && f[3]) applyGT(gt.X, 2);
    if (f[1] && !f[3]) applyGT(gt.X, 3);

    return true;
}

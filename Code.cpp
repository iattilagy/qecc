/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Code.cpp
 * Author: attila
 * 
 * Created on September 23, 2017, 4:19 PM
 */

#include "Code.h"

Code::Code(bool b) {
    input = b;
    deleteError = true;
    mixed = false;
    c = new ket();
}

Code::~Code() {
    if (!mixed) {
        delete c;
    } else {
        delete d;
    }
}

bool Code::setandmesAnc(const std::vector<unsigned> &b, unsigned CS) {
    if (!mixed) {
        ket temp = kron(*c, mket({0}));
        for (int i = 0; b[i] < CS; i++) {
            temp = apply(temp, gt.CNOT,{b[i], CS});
        }
        auto measured = measure(temp, gt.X,{CS});
        return !std::get<0>(measured);
    } else {
        cmat temp;
        temp.noalias() = kron(*d, mket({0}) * mket({0}).adjoint());
        for (int i = 0; b[i] < CS; i++) {
            temp = apply(temp, gt.CNOT,{b[i], CS});
        }
        auto measured = measure(temp, gt.X,{CS});
        return !std::get<0>(measured);
    }
}

void Code::hadamardAllCodeBits() {
    for (unsigned i = 0; i < getCS(); i++) {
        applyGT(gt.H,{i});
    }
}

void Code::hadamardCodeBits(const std::vector<unsigned>& b) {
    for (int i = 0; b[i] < getCS(); i++) {
        applyGT(gt.H,{b[i]});
    }
}

bool Code::getMes(unsigned i) {
    if (!mixed) {
        auto measured = measure(*c, gt.X,{i});
        return !std::get<0>(measured);
    } else {
        auto measured = measure(*d, gt.X,{i});
        return !std::get<0>(measured);
    }
}

void Code::error() {
    while (!errorlist.empty()) {
        Error *e = errorlist.front();
        e->runError(this);
        if (deleteError)
            delete e;
        errorlist.pop();
    }
}
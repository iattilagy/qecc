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

const int Code::TEST = 42;
const int Code::RAND = 43;

Code::Code(bool b) {
    input = b;
}

bool Code::setandmesAnc(const vector<unsigned> &b, unsigned anc) {
    for (int i = 0; b[i] < getCS(); i++) {
        c = apply(c, gt.CNOT,{b[i], anc});
    }
    return getMes(anc);
}

void Code::hadamardAllCodeBits() {
    for (unsigned i = 0; i < getCS(); i++) {
        c = apply(c, gt.H,{i});
    }
}

void Code::hadamardCodeBits(const vector<unsigned>& b){
    for (int i = 0; b[i] < getCS(); i++) {
        c = apply(c, gt.H,{b[i]});
    }
}

bool Code::getMes(unsigned i) {
    auto measured = measure(c, gt.X,{i});
    return !std::get<0>(measured);
}
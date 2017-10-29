/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Single.cpp
 * Author: attila
 * 
 * Created on October 15, 2017, 12:41 PM
 */

#include "Single.h"
#include "Runable.h"
#include "Code5.h"
#include "Steane.h"
#include "Shor.h"
#include "None.h"
#include "BitFlip.h"

std::string Single::getResult() {
    std::ostringstream de;
    de << "BER\t";
    de << runner->getBER() *100 << "%" << std::endl;
    return de.str();
}

void Single::initalize() {
    Code *c;
    for (int i = 0; i < n; i++) {
        if (getCodeType() == Runable::SHOR) {
            c = new Shor(i % 2);
        } else if (getCodeType() == Runable::STEANE) {
            c = new Steane(i % 2);
        } else if (getCodeType() == Runable::CODE5) {
            c = new Code5(i % 2);
        } else if (getCodeType() == Runable::NONE) {
            c = new None(i % 2);
        } else if (getCodeType() == Runable::BITFLIP) {
            c = new BitFlip(i % 2);
        }
        c->addError(e);
        c->disableErrorDeletion();
        runner->addCode(c);
    }
}
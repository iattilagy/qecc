/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.cpp
 * Author: attila
 * 
 * Created on October 13, 2017, 2:40 PM
 */

#include "Test.h"
#include "Shor.h"
#include "Steane.h"
#include "Code5.h"
#include "BitFlip.h"

using namespace std;

const int Test::shorruns = 4 * Shor::CS + 6; //42
const int Test::steaneruns = 5 * Steane::CS;
const int Test::code5runs = 4 * Code5::CS;
const int Test::bitflipruns = BitFlip::CS;

void Test::shorTest(bool input) {
    Shor *s;
    //Add one without any error
    s = new Shor(input);
    runner->addCode(s);
    if (mixed) s->setMixed();
    for (int i = 0; i < Test::shorruns; i++) {
        s = new Shor(input);
        if (mixed) s->setMixed();
        if (i < Shor::CS) {
            Error *e;
            e = new Error(i % Shor::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
        } else if (i < 2 * Shor::CS) {
            Error *e;
            e = new Error(i % Shor::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        } else if (i < 3 * Shor::CS) {
            Error *e;
            e = new Error(i % Shor::CS, Error::CONST);
            e->setError(0, 1, 0);
            s->addError(e);
        } else if (i < 4 * Shor::CS) {
            Error *e;
            e = new Error(i % Shor::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % Shor::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        } else if (i < 4 * Shor::CS + 3) {
            Error *e;
            e = new Error(i % 3, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % 3 + 3, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % 3 + 6, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
        } else {
            Error *e;
            e = new Error(i % 3, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % 3 + 3, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % 3 + 6, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error((i % 3)*3, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        }
        runner->addCode(s);
    }
}

void Test::steaneTest(bool input) {
    Steane *s;
    //Add one without error
    s = new Steane(input);
    runner->addCode(s);
    if (mixed) s->setMixed();
    for (int i = 0; i < Test::shorruns; i++) {
        s = new Steane(input);
        if (mixed) s->setMixed();
        if (i < Steane::CS) {
            Error *e;
            e = new Error(i % Steane::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
        } else if (i < 2 * Steane::CS) {
            Error *e;
            e = new Error(i % Steane::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        } else if (i < 3 * Steane::CS) {
            Error *e;
            e = new Error(i % Steane::CS, Error::CONST);
            e->setError(0, 1, 0);
            s->addError(e);
        } else if (i < 4 * Steane::CS) {
            Error *e;
            e = new Error(i % Steane::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % Steane::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        } else if (i < 5 * Steane::CS) {
            Error *e;
            e = new Error(i % Steane::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(Steane::CS - i % Steane::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        }
        runner->addCode(s);
    }
}

void Test::code5Test(bool input) {
    Code5 *s;
    //Add one without error
    s = new Code5(input);
    runner->addCode(s);
    if (mixed) s->setMixed();
    for (int i = 0; i < Test::code5runs; i++) {
        s = new Code5(input);
        if (mixed) s->setMixed();
        if (i < Code5::CS) {
            Error *e;
            e = new Error(i % Code5::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
        } else if (i < 2 * Code5::CS) {
            Error *e;
            e = new Error(i % Code5::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        } else if (i < 3 * Code5::CS) {
            Error *e;
            e = new Error(i % Code5::CS, Error::CONST);
            e->setError(0, 1, 0);
            s->addError(e);
        } else if (i < 4 * Code5::CS) {
            Error *e;
            e = new Error(i % Code5::CS, Error::CONST);
            e->setError(1, 0, 0);
            s->addError(e);
            e = new Error(i % Code5::CS, Error::CONST);
            e->setError(0, 0, 1);
            s->addError(e);
        }
        runner->addCode(s);
    }
}

void Test::bitFlipTest(bool input) {
    BitFlip *s;
    s = new BitFlip(input);
    runner->addCode(s);
    if (mixed) s->setMixed();
    for (int i = 0; i < Test::bitflipruns; i++) {
        s = new BitFlip(input);
        Error *e;
        e = new Error(i % BitFlip::CS, Error::CONST);
        e->setError(1, 0, 0);
        s->addError(e);
        runner->addCode(s);
    }
}

void Test::initalize() {
    if (getCodeType() == Runable::SHOR) {
        shorTest(0);
        shorTest(1);
    } else if (getCodeType() == Runable::STEANE) {
        steaneTest(0);
        steaneTest(1);
    } else if (getCodeType() == Runable::CODE5) {
        code5Test(0);
        code5Test(1);
    }
}

void Test::runAllTests() {
    cout << "SHOR TESTS" << endl;
    setCodeType(Runable::SHOR);
    run();
    cout << "SHOR\t" << getResult() << endl;

    cout << "STEANE TESTS" << endl;
    setCodeType(Runable::STEANE);
    run();
    cout << "STEANE\t" << getResult() << endl;

    cout << "5QUBIT TESTS" << endl;
    setCodeType(Runable::CODE5);
    run();
    cout << "5QUBIT\t" << getResult() << endl;

    cout << "BITFLIP TESTS" << endl;
    setCodeType(Runable::BITFLIP);
    run();
    cout << "BITFLIP\t" << getResult() << endl;
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runable.h
 * Author: attila
 *
 * Created on October 15, 2017, 12:44 PM
 */

#ifndef RUNABLE_H
#define RUNABLE_H

#include "Runner.h"

class Runable {
public:
    static const int SHOR;
    static const int STEANE;
    static const int CODE5;
    static const int NONE;
    static const int BITFLIP;

    Runable(int type, unsigned maxnumthreads) {
        codetype = type;
        runner = new Runner(maxnumthreads);
    }

    void run() {
        initalize();
        runner->run();
    }
    virtual ~Runable();
    virtual void initalize() = 0;
    virtual std::string getResult() = 0;

    void setCodeType(int t) {
        codetype = t;
    }
protected:
    Runner *runner;

    int getCodeType() {
        return codetype;
    }
private:
    int codetype;
};

#endif /* RUNABLE_H */


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

/**
 * Runable provides container for Runner
 */
class Runable {
public:
    /**
     * Shor code type int
     */
    static const int SHOR;
    /**
     * Steane code type int
     */
    static const int STEANE;
    /**
     * 5qubit code type int
     */
    static const int CODE5;
    /**
     * No coding type int
     */
    static const int NONE;
    /**
     * Bit flip code type int
     */
    static const int BITFLIP;
    /**
     * 4qubit amplitude damping code type int
     */
    static const int AAD4;

    /**
     * Constructor
     * @param type Code type
     * @param maxnumthreads Maximum number of threads running
     */
    Runable(int type, unsigned maxnumthreads, bool p) {
        codetype = type;
        runner = new Runner(maxnumthreads);
        plusminus = p;
        if (p)
            runner->plusMinus();
    }

    /**
     * Runs codes
     */
    void run() {
        initalize();
        runner->run();
    }
    virtual ~Runable();
    /**
     * Initalizes code list.
     * To be defined by child!
     */
    virtual void initalize() = 0;
    /**
     * Returns descriptor string.
     * To be defined by child!
     * @return Log string
     */
    virtual std::string getResult() = 0;

    /**
     * Sets code type to another
     * @param t code type
     */
    void setCodeType(int t) {
        codetype = t;
    }
protected:
    /**
     * Runner to provide multithreading
     */
    Runner *runner;

    /**
     * @return code type
     */
    int getCodeType() {
        return codetype;
    }
private:
    /**
     * Stores code type
     */
    int codetype;

    /**
     * Use ket +, ket - instead ket 0, ket 1
     */
    bool plusminus;
};

#endif /* RUNABLE_H */


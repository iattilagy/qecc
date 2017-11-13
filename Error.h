/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Error.h
 * Author: attila
 *
 * Created on October 13, 2017, 1:31 PM
 */

#ifndef ERROR_H
#define ERROR_H

#include "qpp.h"
using namespace qpp;

class Code;

/**
 * Class to provide errors, friend of Code
 */
class Error {
private:
    /**
     * Type of error, current available: <br>
     * <b>CONST</b>: X, Y or Z error<br>
     * <b>RAND</b>: X, Y or Z error likeliness in per mille<br>
     * <b>ADC</b> : amplitude damping<br>
     */
    int errorType;
    //For random error this these mean likeliness in per mille
    //For const any non zero number will trigger an error 
    /**
     * Likeliness of X error for RAND, X error if not zero for CONST
     */
    unsigned x = 0;
     /**
     * Likeliness of Y error for RAND, Y error if not zero for CONST
     */
    unsigned y = 0;
     /**
     * Likeliness of Z error for RAND, Z error if not zero for CONST
     */
    unsigned z = 0;
    /**
     * Gamma for amplitude damping channel
     */
    double adcg = 0;
    /**
     * Bit to run on (effective if all is false)
     */
    unsigned bit;
    /**
     * If true error is run on all bits of code
     */
    bool all;
public:
    /**
     * CONST type int
     */
    static const int CONST;
    /**
     * RAND type int
     */
    static const int RAND;
    /**
     * ADC type int
     */
    static const int ADC;
    //bit==codesize means all bits

    /**
     * Constructor, runs on all bits
     * @param errt Type
     */
    Error(int errt) {
        this->all = true;
        this->errorType = errt;
    }

    /**
     * Constructor
     * @param bit Subsystem id to run on
     * @param errt Type
     */
    Error(unsigned bit, int errt) {
        this->bit = bit;
        this->all = false;
        this->errorType = errt;
    }
    
    /**
     * Run error on code
     * @param code Code to run on
     */
    void runError(Code *code);
    
    /**
     * Run one bit error on code
     * @param code Code instance
     * @param index Bit to run on
     */
    void runErrorOneBit(Code *code, unsigned index);

    /**
     * Sets X, Y, Z effective if CONST or RAND
     * @param x X error
     * @param y Y error
     * @param z Z error
     */
    void setError(unsigned x, unsigned y, unsigned z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /**
     * Returns descriptor string
     * @return Descriptor
     */
    std::string getError() {
        std::ostringstream de;
        de << x << " " << y << " " << z;
        return de.str();
    }

    /**
     * Sets gamma for amplitude damping effective if ADC
     * @param adcg Gamma
     */
    void setError(double adcg) {
        this->adcg = adcg;
    }
};

#endif /* ERROR_H */


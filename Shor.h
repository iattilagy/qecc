/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shor.h
 * Author: attila
 *
 * Created on September 23, 2017, 2:13 PM
 */

#ifndef SHOR_H
#define SHOR_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;

/**
 * Shor code class
 */
class Shor : public Code {
public:
    /**
     * Code size for Shor is 9
     */
    static const unsigned CS;
    typedef Code super;

    Shor(bool b) : Code(b) {
    }
    bool run() override;
    /**
     * Returns descriptor string <br>
     * Format: <br>
     * <i>SHOR aabbcc zz i->o OK/ERROR</i> <br>
     * Where aabbcc is xflip, zz is zflip
     * @return Log string 
     */
    std::string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return Shor::CS;
    }
private:
    /**
     * Stores measured X ancillas <br>
     * Errors:<br>
     * Block of two ancillas and block of three qubits...<br>
     * 11 -> X error on 1st bit<br>
     * 10 -> X error on 2nd bit<br>
     * 01 -> X error on 3rd bit<br>
     */
    bool xflip[6];
    /**
     * Stores measured Z ancillas<br>
     * 11 -> X error on 1st three bits<br>
     * 10 -> X error on 2nd three bits<br>
     * 01 -> X error on 3rd three bits<br>
     */
    bool zflip[2];
    void errorCorrection(bool *a,
            const std::vector<unsigned> &b);
    void decode();
};

#endif /* SHOR_H */


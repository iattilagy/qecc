/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Code5.h
 * Author: attila
 *
 * Created on September 24, 2017, 2:40 PM
 */

#ifndef CODE5_H
#define CODE5_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;

/**
 * 5Qubit code class 
 */
class Code5 : public Code {
public:
    /**
     * Code size for 5Qubit is 5
     */
    static const unsigned CS;

    Code5(bool b) : Code(b) {

    }
    
    bool run() override;
    
    /**
     * Returns descriptor string <b>
     * Format: <b>
     * <i>5QUBIT aaaa i->o OK/ERROR</i>
     * Where aaaa is flip array
     * @return Log string
     */
    std::string getDescriptor() override;
protected:
    /**
     * Encode 5qubit code
     * @param b Input bit
     */
    void encode(bool b) override;

    unsigned getCS() override {
        return Code5::CS;
    }
    void testError();
private:
    /**
     * Stores measured ancillas<br>
     * Errors (converted to int)<br>
     * 0 -> no error<br>
     * 1 -> X on 0<br>
     * 2 -> z on 2<br>
     * 3 -> X on 4<br>
     * 4 -> Z on 4<br>
     * 5 -> Z on 1<br>
     * 6 -> X on 3<br>
     * 7 -> X+Z on 4<br>
     * 8 -> X on 1<br>
     * 9 -> Z on 3<br>
     * 10 -> Z on 0<br>
     * 11 -> X+Z on 0<br>
     * 12 -> X on 2<br>
     * 13 -> X+Z on 1<br>
     * 14 -> X+Z on 2<br>
     * 15 -> X+Z on 3<br>
     */
    bool flip[4];
    void errorCorrection();
    void decode();
};

#endif /* CODE5_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Steane.h
 * Author: attila
 *
 * Created on September 23, 2017, 4:10 PM
 */

#ifndef STEANE_H
#define STEANE_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;

/**
 * !Steane code class
 */
class Steane : public Code {
public:
    /**
     * Code size for steane is 7
     */
    static const int CS;

    Steane(bool b) : Code(b) {
    }
    bool run() override;
    /**
     * Returns a descriptor string<br>
     * Format:<br>
     * <i>STEANE xxx zzz i->o OK/ERROR</i><br>
     * Where xxx is xflip, zzz is zflip
     */
    std::string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return Steane::CS;
    }
private:
    /**
     * Stores measured X ancillas<br>
     * Converted to int errors:<br>
     *  4 -> error on 0<br>
     *  2 -> error on 1<br>
     *  1 -> error on 2<br>
     *  3 -> error on 3<br>
     *  5 -> error on 4<br>
     *  6 -> error on 5<br>
     *  7 -> error on 6<br>
     */
    bool xflip[3];
     /**
     * Stores measured Z ancillas<br>
     * Converted to int errors:<br>
     *  4 -> error on 0<br>
     *  2 -> error on 1<br>
     *  1 -> error on 2<br>
     *  3 -> error on 3<br>
     *  5 -> error on 4<br>
     *  6 -> error on 5<br>
     *  7 -> error on 6<br>
     */
    bool zflip[3];
    void errorCorrection(bool *a);
    void decode();
};

#endif /* STEANE_H */


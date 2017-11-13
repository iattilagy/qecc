/* 
 * File:   BitFlip.h
 * Author: attila
 *
 * Created on October 23, 2017, 4:07 PM
 */

#ifndef BITFLIP_H
#define BITFLIP_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

using namespace qpp;

/**
 * Bit Flip code class
 */
class BitFlip : public Code {
public:
    /**
     * Code size for bit flip which is 3
     */
    static const unsigned CS;

    BitFlip(bool b) : Code(b) {

    }
    
    bool run() override;
    
    /**
     * Returns descriptor string <br>
     * Format: <br>
     * BITFLIP aa i->o OK/ERROR <br>
     * Where aa is flip array 
     * @return Log string
     */
    std::string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return BitFlip::CS;
    }
private:
    /**
     * Stores measured ancillas<br>
     * 11 -> X error on 1st bit<br>
     * 10 -> X error on 2nd bit<br>
     * 01 -> X error on 3rd bit<br>
     */
    bool flip[2];
    
    void errorCorrection();
    
    void decode();
};

#endif /* BITFLIP_H */


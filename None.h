/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   None.h
 * Author: attila
 *
 * Created on September 24, 2017, 7:18 PM
 */

#ifndef NONE_H
#define NONE_H

#include "qpp.h"
#include "Code.h"
#include <iostream>

class None : public Code {
public:
    static const unsigned CS;

    None(bool b, int errt) : Code(b, errt) {

    }

    bool run();
    string getDescriptor();
protected:
    void encode(bool b);

    unsigned getCS() {
        return None::CS;
    }
    void testError();
private:
};

#endif /* NONE_H */


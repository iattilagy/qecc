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

    None(bool b) : Code(b) {

    }

    bool run() override;
    string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return None::CS;
    }
private:
};

#endif /* NONE_H */


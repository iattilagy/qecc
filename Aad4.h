/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Aad4.h
 * Author: attila
 *
 * Created on October 23, 2017, 3:03 PM
 */

#ifndef AAD4_H
#define AAD4_H

#include "qpp.h"
#include "Code.h"

class Aad4 : public Code {
public:
    static const unsigned CS;

    Aad4(bool b) : Code(b) {

    }
    bool run() override;
    std::string getDescriptor() override;
protected:
    void encode(bool b) override;

    unsigned getCS() override {
        return Aad4::CS;
    }
private:
    bool flip[2];
};

#endif /* AAD4_H */


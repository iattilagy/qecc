/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   None.cpp
 * Author: attila
 * 
 * Created on September 24, 2017, 7:18 PM
 */

#include "None.h"

const unsigned None::CS = 1;

bool None::run() {
    encode(input);
    error();

    result = getMes(0);
    ok = (result == input);
    return result;
}

void None::encode(bool b) {
    c = mket({b});
}

std::string None::getDescriptor() {
    std::ostringstream de;
    de << "NONE\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}




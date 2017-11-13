/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runable.cpp
 * Author: attila
 * 
 * Created on October 15, 2017, 12:44 PM
 */

#include "Runable.h"

const int Runable::SHOR = 100;
const int Runable::STEANE = 101;
const int Runable::CODE5 = 102;
const int Runable::NONE = 103;
const int Runable::BITFLIP = 104;
const int Runable::AAD4 = 105;

Runable::~Runable() {
    delete runner;
}


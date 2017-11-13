/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Single.h
 * Author: attila
 *
 * Created on October 15, 2017, 12:41 PM
 */

#ifndef SINGLE_H
#define SINGLE_H

#include "Runner.h"
#include "Runable.h"


/**
 * Single class runs a single error channel n times
 */
class Single : public Runable {
public:

    /**
     * Constructor
     * @param type Code type
     * @param maxnumthreads Maximum number of threads running
     * @param e Error to apply
     * @param n Number of runs
     */
    Single(int type, int maxnumthreads, Error *e, int n)
    : Runable(type, maxnumthreads) {
        this->e = e;
        this->n = n;
    }

    void initalize() override;

    std::string getResult() override;
private:
    int n;
    Error *e;
};

#endif /* SINGLE_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runner.h
 * Author: attila
 *
 * Created on October 13, 2017, 2:18 PM
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Code.h"

using namespace std;

//This would be run by pthread so not a member
void *runCode(void *c);

class Runner {
public:
    Runner(unsigned maxnumthreads);
    virtual ~Runner();
    void addCode(Code *c);
    void run();

    void waitFor();
    void WaitEmpty();

    //Runner is stopped if stop is true, and all the threads are done
    void reset() {
        errorCounter.store(0, memory_order_relaxed);
        runCounter.store(0, memory_order_relaxed);
    }

    float getBER() {
        return (float) errorCounter.load(std::memory_order_relaxed) 
                / runCounter.load(std::memory_order_relaxed);
    }
private:
    queue<Code *> *codes;
    atomic_int threadCounter;
    atomic_int errorCounter;
    atomic_int runCounter;
    atomic_bool stop;
    unsigned maxnumthreads;
};

#endif /* RUNNER_H */


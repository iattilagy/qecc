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
        errorCounter.store(0);
        runCounter.store(0);
        threadCounter.store(0);
    }

    float getBER() {
        return (float) errorCounter.load(std::memory_order_relaxed) 
                / runCounter.load(std::memory_order_relaxed);
    }
private:
    std::queue<Code *> *codes;
    std::atomic_int threadCounter;
    std::atomic_int errorCounter;
    std::atomic_int runCounter;
    std::atomic_bool stop;
    unsigned maxnumthreads;
};

#endif /* RUNNER_H */


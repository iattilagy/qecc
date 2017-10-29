/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runner.cpp
 * Author: attila
 * 
 * Created on October 13, 2017, 2:18 PM
 */

#include <queue>

#include "Runner.h"
#include <unistd.h>

using namespace std;

void *runCode(void *c) {
    Code *code = ((Code*) c);
    code->run();
    cout << code->getDescriptor();
    if (!code->getOK())
        code->errorCounter->fetch_add(1, memory_order_relaxed);
    code->threadCounter->fetch_sub(1, memory_order_relaxed);
    delete code;
}

Runner::Runner(unsigned t) {
    maxnumthreads = t;
    codes = new queue<Code *>;
}

void Runner::addCode(Code* c) {
    c->errorCounter = &errorCounter;
    c->threadCounter = &threadCounter;
    codes->push(c);
}

void Runner::run() {
    reset();
     while (!codes->empty()) {
        if (!codes->empty() && threadCounter.load(memory_order_relaxed)
                < maxnumthreads) {
            runCounter.fetch_add(1, memory_order_relaxed);
            threadCounter.fetch_add(1, memory_order_relaxed);
            pthread_t t;
            pthread_create(&t, NULL, runCode, codes->front());
            codes->pop();
        }
        usleep(20);
    }
    while (threadCounter.load(memory_order_relaxed)) {
        usleep(100);
    }
}

Runner::~Runner() {
    delete codes;
}


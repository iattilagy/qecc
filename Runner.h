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

/**
 * Function to be run by Runner using pthread
 * @param c Pointer to Code instance to be run
 * @return Unused
 */
void *runCode(void *c);

/**
 * Runs codes multithreaded
 */
class Runner {
public:
    /**
     * Constructor
     * @param maxnumthreads Maximum number of thread running
     */
    Runner(unsigned maxnumthreads);
    virtual ~Runner();
    /**
     * Adds code to code list
     * @param c Pointer to the code to be added
     */
    void addCode(Code *c);

    /**
     * Runs codes in code list
     */
    void run();

    /**
     * Reset status normally run by run()
     */
    void reset() {
        errorCounter.store(0);
        runCounter.store(0);
        threadCounter.store(0);
    }

    /**
     * Get bit error rate
     * @return Bit error rate 
     */
    float getBER() {
        return (float) errorCounter.load(std::memory_order_relaxed)
                / runCounter.load(std::memory_order_relaxed);
    }

    /**
     * Run codes with ket+, ket- inputs
     */
    void plusMinus() {
        plusminus = true;
    }
private:
    /**
     * List of code
     */
    std::queue<Code *> *codes;
    /**
     * Counts running threads
     */
    std::atomic_int threadCounter;
    /**
     * Counts errors
     */
    std::atomic_int errorCounter;
    /**
     * Counts code runs
     */
    std::atomic_int runCounter;

    /**
     * Maximum number of threads to run simultaneously
     */
    unsigned maxnumthreads;

    /**
     * Run code with ket +, ket - inputs
     */
    bool plusminus;
};

#endif /* RUNNER_H */


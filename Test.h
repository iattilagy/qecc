/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.h
 * Author: attila
 *
 * Created on October 13, 2017, 2:40 PM
 */

#ifndef TEST_H
#define TEST_H

#include "Runner.h"
#include "Runable.h"

/**
 * Runs tests for codes
 */
class Test : public Runable {
public:
    /**
     * Number of runs for Shor code
     */
    static const int shorruns;
    /**
     * Number of runs for steane code
     */
    static const int steaneruns;
    /**
     * Number of runs for 5Qubit code
     */
    static const int code5runs;
    /**
     * Number of runs for bit flip code
     */
    static const int bitflipruns;

    /**
     * Initialize for shor
     * @param input input bit
     */
    void shorTest(bool input);
    /**
     * Initialize for steane
     * @param input input bit
     */
    void steaneTest(bool input);
    /**
     * Initialize for 5Qubit
     * @param input input bit
     */
    void code5Test(bool input);
    /**
     * Initialize for bit flip
     * @param input input bit 
     */
    void bitFlipTest(bool input);

    void initalize() override;

    /**
     * Run tests using density matrix notation
     */
    void testMixed() {
        mixed = true;
    }

    /**
     * Descriptor string<br>
     * If all are okay <b>TEST SUCCESFULL</b><br>
     * If some failed <b>SOME TESTS FAILED</b>
     * @return 
     */
    std::string getResult() override {
        if ((int) (runner->getBER()*10000) == 0) {
            return "TESTS SUCCESFULL";
        } else {
            return "SOME TESTS FAILED";
        }
    }
    
    /**
     * Runs all inbuilt tests
     */
    void runAllTests();

    /**
     * @param type Code type
     * @param maxnumthreads Maximum number of threads
     */
    Test(int type, int maxnumthreads) : Runable(type, maxnumthreads) {
        mixed = false;
    }
private:
    /**
     * If true density matrixes are used in codes
     */
    bool mixed;
};

#endif /* TEST_H */


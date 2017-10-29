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

class Test : public Runable {
public:
    static const int shorruns;
    static const int steaneruns;
    static const int code5runs;
    static const int bitflipruns;

    void shorTest(bool input);
    void steaneTest(bool input);
    void code5Test(bool input);
    void bitFlipTest(bool input);

    void initalize() override;

    void testMixed() {
        mixed = true;
    }

    std::string getResult() override {
        if ((int) (runner->getBER()*10000) == 0) {
            return "TESTS SUCCESFULL";
        } else {
            return "SOME TESTS FAILED";
        }
    }
    
    void runAllTests();

    Test(int type, int maxnumthreads) : Runable(type, maxnumthreads) {
        mixed = false;
    }
private:
    bool mixed;
};

#endif /* TEST_H */


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

    void shorTest(bool input);
    void steaneTest(bool input);
    void code5Test(bool input);

    void initalize() override;

    std::string getResult() override {
        if ((int) (runner->getBER()*10000) == 0) {
            return "TESTS SUCCESFULL";
        } else {
            return "SOME TESTS FAILED";
        }
    }

    Test(int type, int maxnumthreads) : Runable(type, maxnumthreads) {

    }
private:
};

#endif /* TEST_H */


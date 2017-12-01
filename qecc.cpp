
/* 
 * File:   qecc.cpp
 * Author: attila
 *
 * Created on September 23, 2017, 2:56 PM
 */

#include <cstdlib>

#include "Shor.h"
#include "Steane.h"
#include "Code.h"
#include "Code5.h"
#include "None.h"
#include "Runner.h"
#include "Test.h"
#include <iostream>
#include <unistd.h>
#include "Single.h"
#include "Network.h"

using namespace std;

volatile int numthreads = 0;
volatile int errRun = 0;

/**
 * Print help for qecc
 */
void printHelp() {
    cout << endl;
    cout << "Usage:" << endl;
    cout << " qecc [options]" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "\t-j <n>\t use n threads (default 2)" << endl;
    cout << "\t-n <m>\t run m times (default 100)" << endl;
    cout << "\t-t\t run inbuilt tests (all must be OK)" << endl;
    cout << "\t-f\t specify network file name" << endl;
    cout << "\t-x\t replace xarg in network files" << endl;
    cout << "\t-c\t specify code possible values" << endl;
    cout << "\t\tshor steane 5qubit bitflip none" << endl;
    cout << endl;
    cout << "\t-h print this help page" << endl;
}

/**
 * Main function of qecc
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
    int max_numthreads = 2;
    int num_of_runs = 100;
    bool test = false;
    string filename = "";
    string codetype = "";
    string x = "";
    int type = 0;
    bool p = false;

    srand(time(NULL));

    int c;
    while ((c = getopt(argc, argv, "hj:n:tf:c:x:p")) != -1) {
        switch (c) {
            case 'j':
                max_numthreads = atoi(optarg);
                if (max_numthreads < 1) {
                    cout << "Number of threads should "
                            << "be greater than 1 exiting...";
                    exit(3);
                }
                break;
            case 'n':
                num_of_runs = atoi(optarg);
                break;
            case 'f':
                filename = optarg;
                break;
            case 'c':
                codetype = optarg;
                if (codetype.compare("shor") == 0) {
                    type = Runable::SHOR;
                } else if (codetype.compare("steane") == 0) {
                    type = Runable::STEANE;
                } else if (codetype.compare("5qubit") == 0) {
                    type = Runable::CODE5;
                } else if (codetype.compare("bitflip") == 0) {
                    type = Runable::BITFLIP;
                } else if (codetype.compare("none") == 0) {
                    type = Runable::NONE;
                } else if (codetype.compare("aad4") == 0) {
                    type = Runable::AAD4;
                }else {
                    cout << "Bad codetype exiting..." << endl;
                    exit(5);
                }
                break;
            case 't':
                test = true;
                break;
            case 'x':
                x = optarg;
                break;
            case 'p':
                p = true;
                break;
            case 'h':
                printHelp();
                exit(0);
        }
    }

    if (test) {
        Test *t = new Test(0, max_numthreads, p);
        t->runAllTests();
        cout << endl << "**************************"
                << endl << "Mixed state tests" << endl
                << "**************************" << endl;
        t->testMixed();
        t->runAllTests();
        delete t;
        return 0;
    }

    if (filename.compare("") != 0) {
        if (!type) {
            cout << "Specify code for network mode" << endl;
            exit(4);
        }
        Network * n = new Network(type,
                max_numthreads, filename, num_of_runs, x, p);
        n->runAll();
        delete n;
        return 0;
    }

    Error *e = new Error(Error::ADC);
    e->setError(0.01);
    Single *s = new Single(Runable::AAD4, max_numthreads, e, 1000, p);
    s->run();
    cout << s->getResult() << endl;
    cout << "Run either in test mode or with filename..." << endl;

    return 0;
}



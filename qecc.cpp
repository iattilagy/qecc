
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

using namespace std;

volatile int numthreads = 0;
volatile int errRun = 0;

void printHelp() {
    cout << endl;
    cout << "Usage:" << endl;
    cout << " qecc [options]" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "\t-j <n>\t use n threads" << endl;
    cout << "\t-n <m>\t run m times" << endl;
    cout << "\t-s\t run Shor code" << endl;
    cout << "\t-7\t run Steane code" << endl;
    cout << "\t-5\t run 5 qubit code" << endl;
    cout << "\t-1\t run non coded" << endl;
    cout << "\t-t\t run inbuilt tests (all must be OK)" << endl;
    cout << "\t-x,-y,-z <per mille> probability of X, Y, Z erros" << endl;
    cout << "\t\t ineffective in test mode!" << endl;
    cout << endl;
    cout << "\t-h print this help page" << endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
    int counter = 0;
    int max_numthreads = 2;
    int num_of_runs = 1000;
    bool shor = false;
    bool steane = false;
    bool code5 = false;
    bool none = false;
    int x = 0, y = 0, z = 0;
    bool test = false;

    srand(time(NULL));

    int c;
    while ((c = getopt(argc, argv, "hj:n:s751x:y:z:t")) != -1) {
        switch (c) {
            case 'j':
                max_numthreads = atoi(optarg);
                if (max_numthreads < 2)
                    exit(3);
                break;
            case 'n':
                num_of_runs = atoi(optarg);
                break;
            case 's':
                shor = true;
                break;
            case '7':
                steane = true;
                break;
            case '5':
                code5 = true;
                break;
            case '1':
                none = true;
                break;
            case 'x':
                x = atoi(optarg);
                break;
            case 'y':
                x = atoi(optarg);
                break;
            case 'z':
                z = atoi(optarg);
                break;
            case 't':
                test = true;
                break;
            case 'h':
                printHelp();
                exit(0);
        }
    }

    cout << "CONFIG\t" << (test ? "TEST\t" : "RAND\t");
    if (!test)
        cout << "RUNS " << num_of_runs << "\t";
    cout << "THREADS " << max_numthreads << "\t";
    if (!test)
        cout << "X " << x << "‰ Y " << y << "‰ Z" << z << "‰";
    cout << endl;


    Test *t = new Test(Runable::STEANE, max_numthreads);
    t->testMixed();
    t->run();
    cout << "STEANE\t" << t->getResult() << endl;
    t->setCodeType(Runable::SHOR);
    t->run();
    cout << "SHOR\t" << t->getResult() << endl;
    t->setCodeType(Runable::CODE5);
    t->run();
    cout << "5QUBIT\t" << t->getResult() << endl;
    delete t;

    /*Error *e = new Error(Steane::CS, Error::RAND);
    e->setError(100, 0, 0);
    Single *s = new Single(Runable::STEANE, max_numthreads, e, 100);
    s->run();
    cout << "SINGLE STEANE\t" << s->getResult() << endl;
    delete s;
    delete e;*/

    return 0;
}



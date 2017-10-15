
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
    int max_numthreads = 10;
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


    Runner *r = new Runner(max_numthreads);
    //Run Shor test with 0
    Test *t = new Test(r);
    t->shorTest(0);
    t->shorTest(1);
    r->run();
    cout << "SHOR\tBER\t" << r->getBER()*100 << "%" << endl;
    t->steaneTest(0);
    t->steaneTest(1);
    r->run();
    cout << "STEANE\tBER\t" << r->getBER()*100 << "%" << endl;
    t->code5Test(0);
    t->code5Test(1);
    r->run();
    cout << "5QUBIT\tBER\t" << r->getBER()*100 << "%" << endl;

    delete t;
    delete r;

    return 0;
}



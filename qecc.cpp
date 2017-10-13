
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
#include <iostream>
#include <unistd.h>

using namespace std;

volatile int numthreads = 0;
volatile int errRun = 0;

void *runCode(void *c) {
    Code *code = ((Code*) c);
    code->run();
    cout << code->getDescriptor();
    if (!code->getOK())
        errRun++;
    delete code;
    numthreads--;
}

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
    int max_numthreads = 1;
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
    cout << "RUNS " << num_of_runs << "\t";
    cout << "THREADS " << max_numthreads << "\t";
    if (!test)
        cout << "X " << x << "‰ Y " << y << "‰ Z" << z << "‰";
    cout << endl;

    while (shor || steane || code5 || none) {
        while (counter < num_of_runs) {
            pthread_t t;
            if (numthreads < max_numthreads) {
                Code *code;
                int errt = test ? Code::TEST : Code::RAND;
                bool input = test ? counter % 2 : rand() % 2;
                if (shor)
                    code = new Shor(input, errt);
                else if (steane)
                    code = new Steane(input, errt);
                else if (code5)
                    code = new Code5(input, errt);
                else if (none)
                    code = new None(input, errt);

                code->setRandErr(x, y, z);
                code->setTestErr(counter / 2);
                pthread_create(&t, NULL, runCode, code);
                numthreads++;
                counter++;
            }
            usleep(25);
        }
        while (numthreads != 0) {
            usleep(50);
        }
        if (shor)
            cout << "SHOR\tBER\t";
        else if (steane)
            cout << "STEANE\tBER\t";
        else if (code5)
            cout << "5QUBIT\tBER\t";
        else if (none)
            cout << "NONE\tBER\t";

        cout << (float) errRun * 100 / num_of_runs << " %\n";
        errRun = 0;
        counter = 0;
        if (shor) shor = false;
        else if (steane) steane = false;
        else if (code5) code5 = false;
        else if (none) none = false;
    }

    return 0;
}



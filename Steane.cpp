/* 
 * File:   Steane.cpp
 * Author: attila
 * 
 * Created on September 23, 2017, 4:10 PM
 */

#include "Steane.h"

const int Steane::CS = 7;

std::string Steane::getDescriptor() {
    std::ostringstream de;
    de << "STEANE\t";
    de << xflip[0] << xflip[1] << xflip [2] << "\t";
    de << zflip[0] << zflip[1] << zflip [2] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void Steane::encode(bool b) {
    *c = mket({0, 0, 0, b ? 1u : 0u, 0, 0, 0});
    if (mixed) {
        convertToMixed();
    }

    applyGT(gt.H,{0});
    applyGT(gt.H,{1});
    applyGT(gt.H,{2});

    applyCGT(gt.CNOT,{3, 4});
    applyCGT(gt.CNOT,{3, 5});

    applyCGT(gt.CNOT,{1, 3});
    applyCGT(gt.CNOT,{1, 5});
    applyCGT(gt.CNOT,{1, 6});

    applyCGT(gt.CNOT,{2, 3});
    applyCGT(gt.CNOT,{2, 4});
    applyCGT(gt.CNOT,{2, 6});

    applyCGT(gt.CNOT,{0, 4});
    applyCGT(gt.CNOT,{0, 5});
    applyCGT(gt.CNOT,{0, 6});
}

void Steane::decode() {
    applyCGT(gt.CNOT,{0, 4});
    applyCGT(gt.CNOT,{0, 5});
    applyCGT(gt.CNOT,{0, 6});

    applyCGT(gt.CNOT,{1, 3});
    applyCGT(gt.CNOT,{1, 5});
    applyCGT(gt.CNOT,{1, 6});

    applyCGT(gt.CNOT,{2, 3});
    applyCGT(gt.CNOT,{2, 4});
    applyCGT(gt.CNOT,{2, 6});

    applyCGT(gt.CNOT,{3, 4});
    applyCGT(gt.CNOT,{3, 5});

    applyGT(gt.H,{0});
    applyGT(gt.H,{1});
    applyGT(gt.H,{2});
}

void Steane::errorCorrection(bool *a) {
    switch (a[0]*4 + a[1]*2 + a[2]) {
        case 4:
            applyGT(gt.X,{0});
            break;
        case 2:
            applyGT(gt.X,{1});
            break;
        case 1:
            applyGT(gt.X,{2});
            break;
        case 3:
            applyGT(gt.X,{3});
            break;
        case 5:
            applyGT(gt.X,{4});
            break;
        case 6:
            applyGT(gt.X,{5});
            break;
        case 7:
            applyGT(gt.X,{6});
            break;
    }
}

bool Steane::run() {
    encode(input);

    error();

    xflip [0] = setandmesAnc({0, 4, 5, 6, CS}, CS);
    xflip [1] = setandmesAnc({1, 3, 5, 6, CS}, CS);
    xflip [2] = setandmesAnc({2, 3, 4, 6, CS}, CS);
    errorCorrection(xflip);

    hadamardAllCodeBits();
    zflip [0] = setandmesAnc({0, 4, 5, 6, CS}, CS);
    zflip [1] = setandmesAnc({1, 3, 5, 6, CS}, CS);
    zflip [2] = setandmesAnc({2, 3, 4, 6, CS}, CS);
    errorCorrection(zflip);
    hadamardAllCodeBits();

    decode();
    result = getMes(3);
    ok = (result == input);
    return result;
}
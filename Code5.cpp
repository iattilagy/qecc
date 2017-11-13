/* 
 * File:   Code5.cpp
 * Author: attila
 * 
 * Created on September 24, 2017, 2:40 PM
 */

#include "Code5.h"

const unsigned Code5::CS = 5;

std::string Code5::getDescriptor() {
    std::ostringstream de;
    de << "5QUBIT\t";
    de << flip[0] << flip[1] << flip [2] << flip[3] << "\t";
    de << input << "->" << result << "\t";
    de << ((input == result) ? "OK" : "ERROR") << std::endl;
    return de.str();
}

void Code5::encode(bool b) {
    *c = mket({b ? 1u : 0u, 0, 0, 0, 0});
    if (mixed) {
        convertToMixed();
    }

    hadamardCodeBits({1, 2, 3, 4, getCS()});

    applyCGT(gt.CNOT,{4, 0});
    applyCGT(gt.CNOT,{3, 0});
    applyCGT(gt.CNOT,{2, 0});
    applyCGT(gt.CNOT,{1, 0});

    applyCGT(gt.CZ,{4, 3});
    applyCGT(gt.CZ,{3, 2});
    applyCGT(gt.CZ,{2, 1});
    applyCGT(gt.CZ,{1, 0});
    applyCGT(gt.CZ,{0, 4});
}

void Code5::decode() {
    applyCGT(gt.CZ,{0, 4});
    applyCGT(gt.CZ,{1, 0});
    applyCGT(gt.CZ,{2, 1});
    applyCGT(gt.CZ,{3, 2});
    applyCGT(gt.CZ,{4, 3});

    applyCGT(gt.CNOT,{1, 0});
    applyCGT(gt.CNOT,{2, 0});
    applyCGT(gt.CNOT,{3, 0});
    applyCGT(gt.CNOT,{4, 0});

    hadamardCodeBits({1, 2, 3, 4, CS});
}

void Code5::errorCorrection() {
    unsigned char ec = 0;
    ec += flip[0];
    ec <<= 1;
    ec += flip[1];
    ec <<= 1;
    ec += flip[2];
    ec <<= 1;
    ec += flip[3];

    switch (ec) {
        case 1:
            applyGT(gt.X, 0);
            break;
        case 2:
            applyGT(gt.Z, 2);
            break;
        case 3:
            applyGT(gt.X, 4);
            break;
        case 4:
            applyGT(gt.Z, 4);
            break;
        case 5:
            applyGT(gt.Z, 1);
            break;
        case 6:
            applyGT(gt.X, 3);
            break;
        case 7:
            applyGT(gt.X, 4);
            applyGT(gt.Z, 4);
            break;
        case 8:
            applyGT(gt.X, 1);
            break;
        case 9:
            applyGT(gt.Z, 3);
            break;
        case 10:
            applyGT(gt.Z, 0);
            break;
        case 11:
            applyGT(gt.X, 0);
            applyGT(gt.Z, 0);
            break;
        case 12:
            applyGT(gt.X, 2);
            break;
        case 13:
            applyGT(gt.X, 1);
            applyGT(gt.Z, 1);
            break;
        case 14:
            applyGT(gt.X, 2);
            applyGT(gt.Z, 2);
            break;
        case 15:
            applyGT(gt.X, 3);
            applyGT(gt.Z, 3);
            break;
    }
}

bool Code5::run() {
    encode(input);

    error();

    hadamardCodeBits({0, 3, CS});
    flip[0] = setandmesAnc({0, 1, 2, 3, CS}, CS);
    hadamardCodeBits({0, 3, CS});

    hadamardCodeBits({1, 4, CS});
    flip[1] = setandmesAnc({1, 2, 3, 4, CS}, CS);
    hadamardCodeBits({1, 4, CS});

    hadamardCodeBits({0, 2, CS});
    flip[2] = setandmesAnc({0, 2, 3, 4, CS}, CS);
    hadamardCodeBits({0, 2, CS});

    hadamardCodeBits({1, 3, CS});
    flip[3] = setandmesAnc({0, 1, 3, 4, CS}, CS);
    hadamardCodeBits({1, 3, CS});

    errorCorrection();

    decode();
    result = getMes(0);
    ok = (result == input);
    return result;
}
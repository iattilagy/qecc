/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Code.h
 * Author: attila
 *
 * Created on September 23, 2017, 4:19 PM
 */

#ifndef CODE_H
#define CODE_H

#include "qpp.h"
#include "Error.h"
#include <iostream>
#include <queue>
#include <atomic>

using namespace qpp;

/**
 * Code class is provides a way to simulate a code on an erroneous channel <br>
 * This is the parent of all specific code classes
 */
class Code {
    friend class Error;
public:
    /**
     * Constructor
     * @param b Input bit 1 or 0
     */
    Code(bool b);

    /**
     * Destructor
     */
    virtual ~Code();

    /**
     * External error counter provided by Runner class.
     * If an error occurs this is incremented.
     */
    std::atomic_int *errorCounter;

    /**
     * Thread counter of Runner class.
     * After run Runner decrements this.
     */
    std::atomic_int *threadCounter;

    /**
     * Function to simulate the transmission and get the result.
     * To be defined in child classes.
     * @return Measured bit at Bob
     */
    virtual bool run() = 0;

    /**
     * Add an error to the error list
     * @param e Pointer to an error to be added
     */
    void addError(Error *e) {
        errorlist.push(e);
    }

    /**
     * Check whether transmission was successful
     * @return True if input is same as result, false if otherwise
     */
    bool getOK() {
        return ok;
    }

    /**
     * Log of run <br>
     * To be defined in child class <br>
     * Contains code type, input, output, ancilla bit measurements <br>
     * Format:<br>
     * <i>CODETYPE ancillas input->result OK/ERROR</i>
     * @return log string
     */
    virtual std::string getDescriptor() = 0;

    /**
     * Normally Errors are deleted by run function.
     * If the given Error instance is being used by multiple Code instances
     * this will disable deletion of it .
     */
    void disableErrorDeletion() {
        deleteError = false;
    }

    /**
     * Converts vector notation to density matrix.
     * <b>Must be called before run!</b>
     * Useful for testing.
     */
    void setMixed() {
        mixed = true;
    }

    /**
     * Run code in ket+, ket- basis
     */
    void plusMinus() {
        plusminus = true;
    }
protected:
    /**
     * Contains state in vector notation
     */
    ket *c;
    /**
     * Contains state in density matrix
     */
    cmat *d;
    /**
     * True if density matrix is used
     */
    bool mixed;
    /**
     * List of errors to be applied
     */
    std::queue<Error *> errorlist;
    /**
     * Input bit, converted to |0> or |1>
     */
    bool input;
    /**
     * Delete Errors on run.
     * True by default.
     */
    bool deleteError;
    /**
     * Measured bit, being set by run
     */
    bool result;
    /**
     * True if result is same as input, false otherwise
     */
    bool ok;

    /**
     * Run code in ket+, ket- basis
     */
    bool plusminus;

    /**
     * Applies CNOT gates controlled by bits in b on ancilla one-by-one.
     * Than measures ancilla and returns its classical value.
     * @param b Bits controlling ancilla
     * @param CS Code size
     * @return Classical value of ancilla
     */
    bool setandmesAnc(const std::vector<unsigned> &b, unsigned CS);
    /**
     * Hadamard transforms all codebits
     */
    void hadamardAllCodeBits();
    /**
     * Hadamard transforms a set of codebits
     * @param b Bits to transform
     */
    void hadamardCodeBits(const std::vector<unsigned> &b);
    /**
     * Measures bit
     * @param i Subsystem id
     * @return Measured classical value
     */
    bool getMes(unsigned i);

    bool getMesH(unsigned i);

    /**
     * Applies errors on c or d
     */
    void error();
    /**
     * Encode input bit
     * @param b Classical input converted to |0> or |1>
     */
    virtual void encode(bool b) = 0;
    /**
     * Return code size of a child
     * @return code size
     */
    virtual unsigned getCS() = 0;

    /**
     * Applies a single qubit gate
     * @param gate Matrix of the gate
     * @param b subsystem id
     */
    void applyGT(const cmat gate, unsigned b) {
        if (!mixed) {
            *c = apply(*c, gate,{b});
        } else {
            *d = apply(*d, gate,{b});
        }
    }

    /**
     * Applies a 2 qubit gate
     * @param gate Matrix of the gate
     * @param b array of two subsystem ids
     */
    void applyCGT(const cmat gate, const std::vector<unsigned>&b) {
        if (!mixed) {
            *c = apply(*c, gate,{b[0], b[1]});
        } else {
            *d = apply(*d, gate,{b[0], b[1]});
        }
    }

    /**
     * Convert vector notation to density matrix.
     * <b>Must be called inside run!</b>
     * From outside class stays the same but inside it will use density matrix.
     * This has a performance drawback but needed for some errors for example
     * amplitude damping.
     * An amplitude damping Error does this conversion automatically.
     */
    void convertToMixed() {
        if (c) {
            d = new cmat();
            d->noalias() = (*c) * c->transpose().conjugate();
            mixed = true;
            delete c;
        }
    }
};

#endif /* CODE_H */
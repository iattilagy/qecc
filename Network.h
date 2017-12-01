/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Network.h
 * Author: attila
 *
 * Created on October 13, 2017, 11:38 AM
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "Node.h"
#include "Channel.h"
#include "Runable.h"
#include <list>

/**
 * Provides parser and Runner for network mode
 */
class Network : public Runable {
public:

    /**
     * Constructor
     * @param type Code type
     * @param maxnumthreads Maximum number of threads running
     * @param filename Input file name
     * @param n Number of times to run one transmission
     */
    Network(int type, unsigned maxnumthreads, std::string filename, int n, std::string x, bool p)
    : Runable(type, maxnumthreads, p) {
        this->filename = filename;
        this->n = n;
        this->x = x;
    }

    virtual ~Network();

    /**
     * Initalizes Runner, using get Channel for one pair.
     * <b>currentPair must be set before!</b>
     */
    void initalize() override;

    /**
     * Returns result string for one transmission
     * @return Descriptor string
     */
    std::string getResult() override;

    /**
     * Runs simulation for each pair of nodes
     */
    void runAll();
private:
    /**
     * Number of times to run
     */
    int n;

    /**
     * Console tunable in network file
     */
    std::string x;

    /**
     * Input filename
     */
    std::string filename;
    /**
     * List of nodes
     */
    std::list<Node *> nodes;
    /**
     * List of channels
     */
    std::list<Channel *> channels;
    /**
     * Node ids currently running for
     */
    int currentPair[2];

    /**
     * Get node from list by id
     * @param id Node id
     * @return Pointer to the node
     */
    Node *findNode(int id) {
        for (Node *n : nodes) {
            if (n->getId() == id)
                return n;
        }
        return NULL;
    }

    void replaceX(std::string &k) {
        if (k.compare("xarg") == 0)
            k = x;
    }

    /**
     * Get node from list in param
     * @param id Node id
     * @param tmp List to search in
     * @return Pointer to the Node
     */
    Node *findNode(int id, const std::list<Node *> &tmp) {
        for (Node *n : tmp) {
            if (n->getId() == id)
                return n;
        }
        return NULL;
    }

    /**
     * Find node from list by name
     * @param name Name to search for
     * @return Pointer to the node
     */
    Node *findNode(std::string name) {
        for (Node *n : nodes) {
            if (n->getName().compare(name) == 0)
                return n;
        }
        return NULL;
    }

    /**
     * Returns list of channels from tId node to rId node, uses DFS.
     * Recursive function...
     * @param tmp Must be nodes if called from outside 
     * @param tId Alice's id
     * @param rId Bob's id
     * @return List of channels from A to B
     */
    std::list<Channel *>* getChannel(std::list<Node *> tmp, int tId, int rId);

    /**
     * Parses the input file and sets up nodes and channels lists
     */
    void parseFile();
};

#endif /* NETWORK_H */


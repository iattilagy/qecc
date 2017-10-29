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

class Network : public Runable {
public:

    Network(int type, unsigned maxnumthreads, std::string filename, int n)
    : Runable(type, maxnumthreads) {
        this->filename = filename;
        this->n = n;
    }

    virtual ~Network();
    
    void initalize() override;

    std::string getResult() override;
    void runAll();
private:
    int n;
    std::string filename;
    std::list<Node *> nodes;
    std::list<Channel *> channels;
    int currentPair[2];

    Node *findNode(int id) {
        for (Node *n : nodes) {
            if (n->getId() == id)
                return n;
        }
        return NULL;
    }

    Node *findNode(int id, const std::list<Node *> &tmp) {
        for (Node *n : tmp) {
            if (n->getId() == id)
                return n;
        }
        return NULL;
    }

    Node *findNode(std::string name) {
        for (Node *n : nodes) {
            if (n->getName().compare(name) == 0)
                return n;
        }
        return NULL;
    }

    std::list<Channel *>* getChannel(std::list<Node *> tmp, int tId, int rId);
    void parseFile();
};

#endif /* NETWORK_H */


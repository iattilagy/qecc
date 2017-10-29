/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Network.cpp
 * Author: attila
 * 
 * Created on October 13, 2017, 11:38 AM
 */

#include "Network.h"
#include <fstream>
#include <list>
#include "Steane.h"
#include "Shor.h"
#include "Code5.h"
#include "BitFlip.h"
#include "Code.h"
#include "None.h"

using namespace std;

list<Channel *>* Network::getChannel(list<Node *> nodes, int tId, int rId) {
    Node *source = findNode(tId);
    list<Node *> tmp(nodes);
    tmp.remove(source);

    for (Channel *c : channels) {
        int nId = c->matchOneGetOther(tId);
        if (nId == rId) {
            list<Channel *> *ret = new list<Channel *>();
            ret->push_front(c);
            return ret;
        } else if (nId) {
            if (findNode(nId, tmp)) {
                list<Channel *>* ret = getChannel(tmp, nId, rId);
                /*If ret is nut null we found receiver, else do nothing here*/
                if (ret) {
                    ret->push_front(c);
                    return ret;
                }
            }
        }
    }

    /*If we found receiver using no neighbours return NULL*/
    return NULL;
}

void Network::runAll() {
    parseFile();
    for (typename list<Node *>::const_iterator i = nodes.begin(),
            end = nodes.end(); i != end; ++i) {
        for (typename list<Node *>::const_iterator j = next(i),
                end = nodes.end(); j != end; ++j) {
            currentPair[0] = (*i)->getId();
            currentPair[1] = (*j)->getId();
            run();
            cout << (*i)->getName() << "->" << (*j)->getName() << "\t";
            cout << "BER\t";
            cout << runner->getBER() *100 << "%" << std::endl;
        }
    }
}

void Network::initalize() {
    Code *c;
    list<Channel *>* clist = getChannel(nodes, currentPair[0], currentPair[1]);
    for (int i = 0; i < n; i++) {
        if (getCodeType() == Runable::SHOR) {
            c = new Shor(i % 2);
        } else if (getCodeType() == Runable::STEANE) {
            c = new Steane(i % 2);
        } else if (getCodeType() == Runable::CODE5) {
            c = new Code5(i % 2);
        } else if (getCodeType() == Runable::NONE) {
            c = new None(i % 2);
        } else if (getCodeType() == Runable::BITFLIP) {
            c = new BitFlip(i % 2);
        }
        for (typename list<Channel *>::const_iterator i = clist->begin(),
                end = clist->end(); i != end; ++i) {
            c->addError((*i)->getError());
        }
        c->disableErrorDeletion();
        runner->addCode(c);
    }
}

Network::~Network() {
    nodes.remove_if([](Node * n) {
        delete n; return true;
    });
    channels.remove_if([](Channel * n) {
        delete n; return true;
    });
}

void Network::parseFile() {
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
        throw "File not found";
    string key;
    while (infile >> key) {
        if (key.compare("node") == 0) {
            Node *n;
            string name;
            infile >> name;
            n = new Node(name);
            nodes.push_back(n);
        } else if (key.compare("channel") == 0) {
            Channel *c;
            Error * e;
            int a[2];
            string tmp;
            for (int i = 0; i < 2; i++) {
                infile >> tmp;
                a[i] = findNode(tmp)->getId();
                if (!a[i])
                    throw string("Node not defined");
            }

            infile >> tmp;
            if (tmp.compare("RAND") == 0) {
                int err[3];
                e = new Error(Error::RAND);
                infile >> err[0] >> err[1] >> err[2];
                e->setError(err[0], err[1], err[2]);
            } else if (tmp.compare("ADC") == 0) {
                e = new Error(Error::ADC);
                double p;
                infile >> p;
                e->setError(p);
            }
            c = new Channel(a[0], a[1], e);
            channels.push_back(c);
        } else {
            throw string("Parse error");
        }
    }
    infile.close();
}

string Network::getResult() {
    list<Channel *>* clist;
    parseFile();
    clist = getChannel(nodes, 2, 8);
    for (Channel *c : *clist) {
        cout << c->debugPrint() << endl;
    }
    delete clist;
    return "afasdfasd";
}
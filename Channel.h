/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Channel.h
 * Author: attila
 *
 * Created on October 15, 2017, 11:37 AM
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#include "Error.h"
#include "Node.h"
#include <queue>

class Channel {
public:

    Channel(int nodeid0, int nodeid1, Error *e) {
        nodeids[0] = nodeid0;
        nodeids[1] = nodeid1;
        this->e = e;
    }

    bool matchId(int nid0, int nid1) {
        return (nodeids[0] == nid0 && nodeids[1] == nid1) ||
                (nodeids[0] == nid1 && nodeids[1] == nid0);
    }

    int matchOneGetOther(int id) {
        if (id == nodeids[0]) {
            return nodeids[1];
        } else if (id == nodeids[1]) {
            return nodeids[0];
        } else {
            return 0;
        }
    }

    int *getIds() {
        return nodeids;
    }

    std::string debugPrint() {
        std::ostringstream de;
        de << nodeids[0] << "\t";
        de << nodeids[1] << "\t";
        de << e->getError() << "\t";
        return de.str();
    }

    Error *getError() {
        return e;
    }
    Error *e;
    int nodeids[2];

    ~Channel() {
        delete e;
    }
};

#endif /* CHANNEL_H */


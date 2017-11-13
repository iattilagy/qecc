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

/**
 * Used by network mode <br>
 * Stores two node ids and an error between them
 */
class Channel {
public:

    /**
     * Constuctor
     * @param nodeid0 Id of first node
     * @param nodeid1 Id of second node
     * @param e Error of the channel
     */
    Channel(int nodeid0, int nodeid1, Error *e) {
        nodeids[0] = nodeid0;
        nodeids[1] = nodeid1;
        this->e = e;
    }

    /**
     * Check if two ids given is what we have, order does not matter
     * @param nid0 First node id
     * @param nid1 Second node id
     * @return True if our ids match the input
     */
    bool matchId(int nid0, int nid1) {
        return (nodeids[0] == nid0 && nodeids[1] == nid1) ||
                (nodeids[0] == nid1 && nodeids[1] == nid0);
    }

    /**
     * Check if one of our ids is same as input and return the
     * other or zero if no match
     * @param id Node id
     * @return The id of our other node on match
     */
    int matchOneGetOther(int id) {
        if (id == nodeids[0]) {
            return nodeids[1];
        } else if (id == nodeids[1]) {
            return nodeids[0];
        } else {
            return 0;
        }
    }

    /**
     * Get node ids
     * @return Array of our the nodeids
     */
    int *getIds() {
        return nodeids;
    }

    /**
     * Print data to string
     * @return String which describes the instance
     */
    std::string debugPrint() {
        std::ostringstream de;
        de << nodeids[0] << "\t";
        de << nodeids[1] << "\t";
        de << e->getError() << "\t";
        return de.str();
    }

    /**
     * Get Error
     * @return returns pointer to error
     */
    Error *getError() {
        return e;
    }
    
    ~Channel() {
        delete e;
    }
private:
    /**
     * Channel error
     */
    Error *e;
    
    /**
     * Node ids
     */
    int nodeids[2];
};

#endif /* CHANNEL_H */


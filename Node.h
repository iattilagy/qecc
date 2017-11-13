/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: attila
 *
 * Created on October 15, 2017, 11:41 AM
 */

#ifndef NODE_H
#define NODE_H

#include <atomic>
#include <string>

/**
 * Assigns a unique id to a name
 */
class Node {
public:

    /**
     * Constructor
     * @param n Name of the node
     */
    Node(std::string n) : id(++s_id), name(n) {
    }

    /**
     * Returns Id
     * @return id
     */
    int getId() {
        return id;
    }

    /**
     * Return name
     * @return name
     */
    std::string getName() {
        return name;
    }
private:
    /**
     * Unique id of this instance
     */
    int id;
    /**
     * Name if the node
     */
    std::string name;
    /**
     * Global id counter
     */
    static std::atomic_int s_id;
};

#endif /* NODE_H */


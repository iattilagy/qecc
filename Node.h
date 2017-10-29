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

class Node {
public:

    Node(std::string n) : id(++s_id), name(n) {
    }

    int getId() {
        return id;
    }

    std::string getName() {
        return name;
    }
private:
    int id;
    std::string name;
    static std::atomic_int s_id;
};

#endif /* NODE_H */


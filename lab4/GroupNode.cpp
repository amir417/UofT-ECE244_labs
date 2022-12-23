//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupNode class below




#include "GroupNode.h"

// class GroupNode {
// private:
//     string name;                           // name ofthe group
//     ShapeList* myShapeList;                // pointer to the list of shapes in group
//     GroupNode* next ;                      // pointer to next node in the list
// public:
//     GroupNode(string n);                   // sets group name to n and makes myShapeList
//                                            // point to a new ShapeList; sets next to nullptr
//     ~GroupNode();                          // deletes the myShapeList list
//     string getName() const;                // returns group name
//     ShapeList* getShapeList() const;       // returns myShapeList
//     void setShapeList(ShapeList* ptr);     // sets myShapeList to ptr
//     GroupNode* getNext() const;            // returns next
//     void setNext(GroupNode* ptr);          // sets next to ptr
//     void print() const;                    // prints the GroupNode
// };

// #endif /* GroupNode_h */

GroupNode::GroupNode(string n){
    name = n;
    myShapeList = new ShapeList();
    next = NULL;
}

GroupNode::~GroupNode(){
    myShapeList->~ShapeList(); 
    myShapeList = NULL;
}

string GroupNode::getName() const{
    return name;
}

ShapeList* GroupNode::getShapeList() const{
    return myShapeList;
}

void GroupNode::setShapeList(ShapeList* ptr){
    myShapeList = ptr;
}

GroupNode* GroupNode::getNext() const{
    return next;
}

void GroupNode::setNext(GroupNode* ptr){
    next = ptr;
}

void GroupNode::print() const{
    cout << name << ":" << endl;
    myShapeList->print(); //not sure about this one
}

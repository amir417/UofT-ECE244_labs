//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeNode class below


#include "ShapeNode.h"

// class ShapeNode {
// private:
//     Shape* myShape;
//     ShapeNode* next;
// public:
//     ShapeNode();                   // sets myShape and next to nullptr
//     ~ShapeNode();                  // deletes the shape pointed to by myShape
//     Shape* getShape() const;       // returns myShape
//     void setShape(Shape* ptr);     // sets myShape to ptr
//     ShapeNode* getNext() const;    // returns next
//     void setNext(ShapeNode* ptr);  // sets next to ptr
//     void print() const;            // prints the ShapeNode
// };

// #endif /* ShapeNode_h */

ShapeNode::ShapeNode (){
    myShape = NULL;
    next  = NULL;
}

ShapeNode::~ShapeNode(){
    delete myShape;
    myShape = NULL;
    // delete next; //not sure
}

Shape* ShapeNode::getShape ()const {
    return myShape;
}

void ShapeNode::setShape (Shape* ptr){
    myShape = ptr;
}

ShapeNode* ShapeNode::getNext() const{
    return next;
}

void ShapeNode::setNext(ShapeNode* ptr){
    next = ptr;
}

void ShapeNode::print() const{
    if (myShape != NULL){
        myShape->draw();
    }
    // cout << myShape->getName() << ": " << myShape->getType() << " " << myShape->getXlocation() << " " << myShape->getYlocation() << " " << myShape->getXsize() << " " << myShape->getYsize() << endl;
} 
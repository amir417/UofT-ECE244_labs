//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below



#include "ShapeList.h"
#include <iostream>
#include <string>
using namespace std;

// class ShapeList {
// private:
//     ShapeNode* head;
// public:
//     ShapeList();                        // sets head to nullptr
//     ~ShapeList();                       // deletes all list nodes starting
//                                         // with head plus associated Shapes
    
//     ShapeNode* getHead() const;         // returns the head pointer
//     void setHead(ShapeNode* ptr);       // sets the head pointer to ptr
    
//     ShapeNode* find(string name) const; // finds a shape node with the specified shape name
//                                         // returns a pointer to the node if found, otherwise
//                                         // returns nullptr if the node is not found
//     void insert(ShapeNode* s);          // inserts the node pointed to by s at the end
//                                         // of the list; s should never be nullptr
//     ShapeNode* remove(string name);     // removes the node with the shape called name
//                                         // returns a pointer to the removed node or
//                                         // nullptr is a node with name does not exist
//     void print() const;                 // prints the list
// };

ShapeList::ShapeList(){
    head = NULL;
}

ShapeList::~ShapeList(){
    ShapeNode* p;
    while (head != NULL){
        p = head;
        head = head->getNext();
        p->~ShapeNode();
        delete p;
    }
    head = NULL;   
    // if (head != NULL){
    //     ShapeNode* p = head->getNext();
    //     ShapeNode* p2 = p;
    //     delete head;
    //     while (p2!=NULL)
    //     {
    //         p2 = p2->getNext();
    //         delete p; //not fully sure about this one but it makes sense
    //         p = p2;
    //     }
    // }
    // else if (head == NULL){
    //     delete head;
    // }
}

ShapeNode* ShapeList::getHead() const{
    return head;
}

void ShapeList::setHead (ShapeNode* ptr){
    head = ptr;
}

ShapeNode* ShapeList::find(string name) const{
    ShapeNode* p = head;
    while (p != NULL && (p->getShape()->getName() != name)){
        p = p->getNext();
    }
    if (p==NULL){
        return NULL;
    }
    else{
        return p;
    }
}

void ShapeList::insert(ShapeNode* s){
    if (s == NULL){
        return;
    }
    else if (head == NULL){
        head = s;
    }
    else{
        ShapeNode* p = head;        
        while (p->getNext()!=NULL)
        {
            p = p->getNext();
        }
        p->setNext(s);
    }
    return;
}

ShapeNode* ShapeList::remove(string name){
    ShapeNode* loc = NULL;
    ShapeNode* temp = NULL;

    if (this->find(name) != NULL){
        if (head->getShape()->getName() == name){
            loc = head;
            temp = head->getNext();
            head->setNext(NULL);
            head = temp;
            return loc;
        }
        else {
            for (ShapeNode* current = head; current->getNext() != NULL; current = current->getNext()){
                if (current->getNext()->getShape()->getName() == name){
                    loc = current->getNext();
                    temp = current ->getNext()->getNext();
                    current->getNext()->setNext(NULL);
                    current->setNext(temp);
                    return loc;
                }
            }
        }
    }

    return NULL;


    // ShapeNode* p= head;
    // ShapeNode* p2 = NULL;
    // while (p != NULL && (p->getShape()->getName() != name)){
    //     p2 = p;
    //     p = p->getNext();
    // }
    // if (p->getShape()->getName() == name){
    //     p2->setNext(p->getNext());
    //     ShapeNode* p3 = p;
    //     p->~ShapeNode(); 
    //     delete p;
    //     return p3;
    // }
    // else{
    //     return NULL;
    // }    
}


void ShapeList::print() const{
    ShapeNode* p = head;
    while ( p!= NULL){
         p->print(); 
        p = p->getNext();
    }
} 
//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below



#include "GroupList.h"


// class GroupList {
// private:
//     GroupNode* head;                  // Pointer to the first GroupNode of the list
// public:
//     GroupList();                      // sets head to nullptr
//     ~GroupList();                     // deletes all list nodes, including all the ShapeList
//                                       // attached to each GroupNode
    
//     GroupNode* getHead() const;       // returns the head pointer
//     void setHead(GroupNode* ptr);     // sets the head pointer to ptr
//     void insert(GroupNode* s);        // inserts the node pointed to by s at the end of the list
//     GroupNode* remove(string name);   // removes the group with the name "name" from the list
//                                       // and returns a pointer to the removed GroupNode
//                                       // returns nullptr is name is not found on list
//     void print() const;               // prints the list, one GroupNode at a time
// };

// #endif /* GroupList_h */

GroupList::GroupList(){
    head = NULL;
}

GroupList::~GroupList(){
    GroupNode* p;
    while (head != NULL){
        p = head;
        head = p->getNext();
        p->~GroupNode();
        delete p;
    }
    head = NULL;
    // if (head == NULL){
    //     delete head;
    // }
    // else {
    //     GroupNode* p = head->getNext();
    //     GroupNode* p2 = head->getNext();
    //     delete head;
    //     while (p2!=NULL){
    //         p2 = p2->getNext();
    //         p->~GroupNode();
    //         delete p;
    //         p = p2;
    //     }
    // }
}

GroupNode* GroupList::getHead() const {
    return head;
}

void GroupList::setHead(GroupNode* ptr){
    head = ptr;
}

void GroupList::insert(GroupNode* s){
    if (head==NULL){
        head = s;
        return;
    }
    else {
        GroupNode* p = head;
        GroupNode* p2 = NULL;
        while (p != NULL){
            p2 = p;
            p = p->getNext();
        }
        p2->setNext(s);
        return;
    }
}

// GroupNode* GroupList::remove(string name){
//     GroupNode* p;
//     GroupNode* p2 = NULL;
//     p = head;
//     while (p != NULL && (p->getName() != name)){
//         p2 = p;
//         p = p->getNext();
//     }
//      if (p->getName() == name){
//         p2->setNext(p->getNext());
//         GroupNode* p3 = p;
//         delete p->getNext();
//         delete p;
//         return p3;
//     }
//     else return NULL;
// }


GroupNode* GroupList :: remove(string name){
        GroupNode* loc = NULL;
        GroupNode* temp = NULL;
        if(head->getName() == name){
            loc = head;
            temp = head->getNext();
            head->setNext(NULL);
            head = temp;
            return loc;
        }
        else{
            for(GroupNode* current = head; current->getNext() != NULL; current = current -> getNext()){
                if(current->getNext()->getName() == name){
                    loc = current -> getNext();
                    temp = current -> getNext()->getNext();
                    current->getNext()->setNext(NULL);
                    current->setNext(temp);
                    return loc;
                }
            }
        }
        return NULL;
    }

void GroupList::print() const{
    // cout << head->getName() << ":" << endl;
    GroupNode* p = head;
    while (p != NULL){
        p->print();
        p= p->getNext();
    }

}
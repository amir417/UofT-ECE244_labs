//
//  parser.cpp
//  Lab4
// ~ece244i/public/exercise 4 Parser.exe
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

void insertShape (Shape* sh1, GroupNode* poolGroup){
    ShapeNode* sNode = new ShapeNode();
    sNode->setShape(sh1);
    // if (poolGroup->getShapeList()== NULL){
    //      ShapeList* sList = new ShapeList();
    //     poolGroup->setShapeList(sList);
    //     sList->insert(sNode);
    // }
    // else if (poolGroup->getShapeList()!= NULL){
    //     poolGroup->getShapeList()->insert(sNode);
    // }
    poolGroup->getShapeList()->insert(sNode);
}



bool nameCheck (string name) {
     bool flag = false;
     for (int i = 0; i < NUM_KEYWORDS; i++){
        if ( name == keyWordsList[i])
            flag = true;
    }
    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i])
            flag = true;
    }
    if (flag == true) {
        cout << "error: invalid name" << endl;
        return false;
    }
    GroupNode* current = gList->getHead();
    while (current != NULL){
        if ((current->getShapeList()->find(name) != NULL) || (current->getName() == name)){
            cout << "error: name " << name << " exists" << endl;
            return false;
        }
        else {current = current->getNext();}  
    }
    return true;
}

bool groupCheck (string name){
    bool flag = false;
     for (int i = 0; i < NUM_KEYWORDS; i++){
        if ( name == keyWordsList[i])
            flag = true;
    }
    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i])
            flag = true;
    }
    if (flag == true) {
        cout << "error: invalid name" << endl;
        return false;
    }
    GroupNode* current = gList->getHead();
    while (current != NULL){
        if (current->getName() == name){
            cout << "error: name " << name << " exists" << endl;
            return false;
        }
        else {current = current->getNext();}  
    }
    return true;
}


bool moveNameCheck (string name, string group) {
     bool flag = false;
     for (int i = 0; i < NUM_KEYWORDS; i++){
        if ( name == keyWordsList[i] || group == keyWordsList[i])
            flag = true;
    }
    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i] || group == shapeTypesList[i])
            flag = true;
    }
    if (flag == true) {
        cout << "error: invalid name" << endl;
        return false;
    }
    GroupNode* current = gList->getHead();
    bool isShape = false;
    bool isGroup = false;
    while (current != NULL){
        if ((current->getShapeList()->find(name) != NULL) ){
            isShape = true;
        }
        else if (current->getName() == group){
            isGroup = true;
        }
        current = current->getNext();  
    }
    if (!isShape){
        cout << "error: shape " << name << " not found" << endl;
        return false;
    }
    else if (!isGroup){
        cout << "error: group " << group << " not found" << endl;
        return false;
    }
    return true;
}

int deleteNameCheck (string name){
     bool flag = false;
     for (int i = 0; i < NUM_KEYWORDS; i++){
        if ( name == keyWordsList[i] )
            flag = true;
    }
    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i])
            flag = true;
    }
    if (flag == true) {
        cout << "error: invalid name" << endl;
        return 0;
    }
    GroupNode* current = gList->getHead();
    bool isShape = false;
    while (current != NULL){
        if ((current->getShapeList()->find(name) != NULL) ){
            isShape = true;
            return 1; //  1 represents that we are removing a shape.
        }
        else if (current->getName() == name){
            return 2; // 2 represents that we are removing a group.
        }
        current = current->getNext();  
    }
    if (!isShape){
        cout << "error: shape " << name << " not found" << endl;
        return 0;
    }
    return 0;
}

int main() {
    gList = new GroupList(); // new groupList is created with head = null
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    string name, type, gName, shapeN1, groupN2;
    int x_loc, y_loc, x_size, y_size;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        if (command == "shape"){
            lineStream >> name >> type >> x_loc >> y_loc >> x_size >> y_size;
            if (nameCheck(name)){
                Shape* sh1 = new Shape (name, type, x_loc, y_loc, x_size, y_size);
                insertShape (sh1, poolGroup);
                sh1->draw();   
            }
        }
        
        else if (command == "group"){
            lineStream >> gName;
            if (groupCheck(gName)){
                GroupNode* gNode = new GroupNode(gName);
                gList->insert(gNode);
                cout << gName << ": group" << endl;
            }
        }
        else if (command == "draw"){
            cout << "drawing:" << endl;
            gList->print();
             
        } 
        else if (command == "move"){
            lineStream >> shapeN1 >> groupN2; // name #1 is the name of the shape to be moved. name #2 is the name of the group to be moved to.
            if (moveNameCheck(shapeN1, groupN2)){
                GroupNode* moveGroup;
                GroupNode* current = gList->getHead();
                GroupNode* current1 = gList->getHead();
                ShapeNode* ptr = NULL;
                while (current != NULL){
                    if (current->getShapeList()->find(shapeN1) != NULL){
                        ptr = current->getShapeList()->find(shapeN1);
                        current->getShapeList()->remove(shapeN1);
                    }
                current = current->getNext();  
                }
                while (current1 != NULL){
                     if (current1->getName() == groupN2){
                        current1->getShapeList()->insert(ptr);
                        cout << "moved " << shapeN1 << " to " << groupN2 << endl;
                     }  
                     current1 = current1->getNext(); 
                 }
            }
        } 
        else if (command == "delete"){
          lineStream >> name;
          ShapeNode* ptr = NULL;
          ShapeList* curNode = NULL;
          if (deleteNameCheck(name) == 0) {goto dest;}
          else if (deleteNameCheck(name) == 1){ //we remove a shape.
                GroupNode* current = gList->getHead();
                while (current != NULL){
                     if (current->getShapeList()->find(name) != NULL){
                        // ptr = current->getShapeList()->find(name);
                        delete (current->getShapeList()->remove(name));
                        // current->getShapeList()->remove(name) = NULL;
                        cout << name << ": deleted" << endl;
                        goto dest;
                        // ptr->~ShapeNode();
                    }
                     current = current->getNext();
                }
          }  
          else if (deleteNameCheck(name) == 2){ //we remove a group
            GroupNode* current = gList->getHead();
            GroupNode* currentprev = gList->getHead();
            GroupNode* ptr = NULL;
            GroupNode* group = NULL;


        
            while (current != NULL){
                if (current->getName() == name) {  

            group = gList->remove(name);        
            curNode = current->getShapeList();
            // cout <<  curNode->getShape()->getName() << endl;
            while (curNode->getHead() != NULL){
                poolGroup->getShapeList()->insert (curNode->remove(curNode->getHead()->getShape()->getName()));
            }   
                    delete group;
                    delete curNode;
                    group = NULL; 
                    cout << name << ": deleted" << endl;
                    goto dest;
                }
                currentprev = current;
                current = current->getNext();
            }
        }
        }
        dest:


        cout << "> ";         
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}
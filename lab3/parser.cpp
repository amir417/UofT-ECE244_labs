// ~ece244i/public/exercise 3 parser.exe
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;
int counter=0;
string currentCommand;
string Gtype, Gname;
int Gval;
int GxSize,GySize,GxLoc,GyLoc,Grotate;
// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool NameTaken(string name){
    for (int i = 0; i < max_shapes; i++)
    {
        if (shapesArray[i] != NULL && name == shapesArray[i]->getName())
        {
        return true;
        }
    }
    return false;
}

bool rotate(stringstream& line){
        if (line.eof()) {
        cout << "Error: too few arguments" << endl;
        return true;
    }
    int z;
    line >> z;
    counter++;
    if (line.fail() || (line.peek() != EOF && line.peek() != 32)){
        cout << "Error: invalid argument" << endl;
        return true;
    }
    else if (z > 360 || z < 0 ){
        cout << "Error: invalid value" << endl;
        return true;
    }
        if(!line.eof() && currentCommand == "rotate"){
        cout << "Error: too many arguments" <<endl;
        return true;
    }
        return false;

}


bool CheckName(stringstream& line){
    if (line.eof()){
      cout << "Error: too few arguments" << endl;
        return true;
    }
    counter ++;
    string name;
    line >> name;


    if (line.fail()||(line.peek() != EOF && line.peek() != 32)){
    cout << "Error: invalid arguments" << endl;
    return true;
    }

    int count = 0;

    for (int i = 0; i < NUM_KEYWORDS; i++){
        if (name == keyWordsList[i])
            count++;
    }
     for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i]){
            count++;
        }
     }

    if (count !=0 && ((currentCommand != "draw" ||  currentCommand != "delete") && name != "all")){
     cout << "Error: invalid shape name" << endl;
     return true;
    }
    if(NameTaken(name) == false && (currentCommand == "draw" && currentCommand == "move"  && currentCommand == "rotate")&& name!="all") {
         cout << "Error: shape " << name << " not found" << endl;
         return true;
        }

    for(int i=0;i<max_shapes;i++){
        if(NameTaken(name) && currentCommand == "create"){
          cout << "Error: shape "<< name << " exists" << endl;
          return true;
        }
    }

        if(!line.eof() && currentCommand == "draw"){
        cout << "Error: too many arguments" <<endl;
        return true;
    }

   Gname = name; 
    return false;

}

int getShapeIndex (string name){
        for (int i = 0; i < max_shapes; i++){
        if (name == shapesArray[i]->getName()){
            return i;
        }
}
return -1;
}

bool CheckType(stringstream& line){
    if (line.eof()){
      cout << "Error: too few arguments" << endl;
        return true;
    }
    counter++;
    string type;
    line >> type;

    if (line.fail()||(line.peek() != EOF && line.peek() != 32)){
    cout << "Error: invalid arguments" << endl;
    return true;
    }

    int count = 0;
        for (int i = 0; i < NUM_TYPES; i++){
        if (type == shapeTypesList[i]){
            count++;
        }
    }

    if (count==0){
     cout << "Error: invalid shape type" << endl;
     return true;
    }

   Gtype = type;
    return false;
}

bool CheckXLoc(stringstream& line){
    if (line.eof()) {
        cout << "Error: too few arguments" << endl;
        return true;
    }
    int x;
    line >> x;
    counter++;
    if (line.fail()|| (line.peek() != EOF && line.peek() != 32)){
        cout << "Error: invalid argument" << endl;
        return true;
    }
    else if (line.peek() == '.' || x < 0){
        cout << "Error: invalid value" << endl;
        return true;
    }

GxLoc = x;
        return false;
}
bool CheckYLoc(stringstream& line){
        if (line.eof()) {
        cout << "Error: too few arguments" << endl;
        return true;
    }
    int y;
    line >> y;
    counter++;
    if (line.fail()||(line.peek() != EOF && line.peek() != 32)){
        cout << "Error: invalid argument" << endl;
        return true;
    }
    else if (line.peek() == '.' || y < 0){
        cout << "Error: invalid value" << endl;
        return true;
    }

        if(!line.eof() && currentCommand == "move"){
        cout << "Error: too many arguments" <<endl;
        return true;
    }
    GyLoc = y;


        return false;
}
bool CheckXSize(stringstream& line){
    if (line.eof()) {
        cout << "Error: too few arguments" << endl;
        return true;
    }
    int x;
    line  >> x;
    counter++;
    if (line.fail()|| (line.peek() != EOF && line.peek() != 32)){
        cout << "Error: invalid argument" << endl;
        return true;
    }
    else if (x < 0 || line.peek() == '.'){
        cout << "Error: invalid value" << endl;
        return true;
    }
     GxSize = x;
        return false;

}

bool CheckYSize(stringstream& line){
        if (line.eof()) {
        cout << "Error: too few arguments" << endl;
        return true;
    }
    int x;
    line >> x;
    counter++;
    if (line.fail()|| (line.peek() != EOF && line.peek() != 32)){
        cout << "Error: invalid argument" << endl;
        return true;
    }
    else if (x < 0 || line.peek() == '.'){
        cout << "Error: invalid value" << endl;
        return true;
    }
    GySize = x;
    if((GySize != GxSize)&& Gtype == "circle"){
        cout << "Error: invalid value" << endl;
        return true; 
    } 

    if(!line.eof() && currentCommand == "create"){
        cout << "Error: too many arguments" <<endl;
        return true;
    }

        return false;
}
bool CheckArray(){
    if (max_shapes < shapeCount){
        cout << "Error: shape array is full" << endl;
        return true;
    }
    return false;
}

bool checkInputs(stringstream& line){
if (CheckName(line) || CheckType(line) ||CheckXLoc(line) || CheckYLoc(line) ||CheckXSize(line)|| CheckYSize(line) ||CheckArray()){
    return false;
}
return true;
}

int main() {

    string line;
    string command, type,name;
    int val;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        counter = 0;
        int errorSent=0;
        command = "";
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        currentCommand = command;
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if(command != "maxShapes" && command != "create" && command != "move" && command != "rotate" && command != "draw" && command != "delete"){
            cout << "Error: invalid command" << endl ;
            errorSent = 1;
        }
        else if(lineStream.peek()== -1 && errorSent == 0){
             cout << "Error: too few arguments" << endl ;
             errorSent = 1;
        }
        else {
            if(command == "maxShapes"){
                lineStream >> val;
                currentCommand = "maxShapes";
                if(lineStream.fail()||((lineStream.peek() != EOF && lineStream.peek() != 32) && errorSent == 0)){
                    cout << "Error: invalid argument" << endl ;
                    errorSent=1;
                }
                else if((val < 0) && errorSent == 0){
                    cout << "Error: invalid value" << endl ;
                    errorSent=1;
                }
                else if (!lineStream.eof() && errorSent == 0){
                    cout << "Error: too many arguments" << endl;
                    errorSent=1;
                }

                 else {
                    max_shapes = val;
                    max_shapes = max_shapes - 1;
                    if(shapesArray == NULL){
                        shapesArray = new Shape* [max_shapes];
                        for (int i; i < max_shapes; i++){
                            shapesArray[i] = NULL;
                        }
                    }
                    else {
                        for (int i; i < max_shapes; i++){
                            if(shapesArray[i]!=NULL){
                                delete shapesArray[i];
                                shapesArray[i] = NULL;
                            }
                        }
                        shapesArray = new Shape* [max_shapes];
                        for (int i; i < max_shapes; i++){
                            shapesArray[i] = NULL;
                        }
                    }
                    cout << "New database: max shapes is " << max_shapes + 1 << endl;
                 }
            }
            if (command == "create"){
                currentCommand = "create";
                if(errorSent == 0 && checkInputs(lineStream) && counter == 6){
                    shapesArray[shapeCount++] = new Shape(Gname,Gtype,GxLoc,GxSize,GyLoc,GySize);
                    cout << "Created " << Gname << ": " << Gtype << " " <<  GxLoc << " "  << GyLoc << " " << GxSize << " " << GySize <<endl;
               }
                else {
                    errorSent = 1;
                }
            }

                if (command == "draw"){
                  currentCommand = "draw";
                if((errorSent == 0 && !CheckName(lineStream))){
                   if (Gname == "all"){
                    cout << "Drew all shapes" << endl;
                    for (int i; i < max_shapes; i++){
                    if(shapesArray[i] != NULL){
                    shapesArray[i] -> draw();
                    }
                    }
                  }
                  else if(NameTaken(Gname)) {
                    if (getShapeIndex(Gname) != -1){
                    cout << "Drew ";
                    shapesArray[getShapeIndex(Gname)] -> draw();
                    }
                    else if(errorSent == 0) {
                        cout << "Error: shape " << Gname << " not found" << endl;
                        errorSent = 1;
                    }
                  }
                  else {
                      cout << "Error: shape " << Gname << " not found" << endl;
                      errorSent = 1;
                  }
                }
                else {
                    errorSent = 1;
                }
                }


            if (command == "move"){
                currentCommand = "move";
                if(errorSent == 0 && !CheckName(lineStream) && !CheckXLoc(lineStream) && !CheckYLoc(lineStream) && counter == 3){
                if (!NameTaken(Gname)){
                      cout << "Error: shape " << Gname << " not found" << endl;
                      errorSent = 1;
                  }
                  else {
                    cout << "Moved " << Gname << " to " << GxLoc << " "  << GyLoc << endl; 
                    shapesArray[getShapeIndex(Gname)] -> setXlocation(GxLoc);   
                    shapesArray[getShapeIndex(Gname)] -> setYlocation(GyLoc);                 
                    }
                }
                else {
                    errorSent = 1;
                }
            }


            if (command == "rotate"){
                currentCommand = "rotate";
                if(errorSent == 0 &&  !CheckName(lineStream) && !rotate(lineStream) && counter == 1){
                   if (!NameTaken(Gname)){
                      cout << "Error: shape " << Gname << " not found" << endl;
                      errorSent = 1;
                  }
                  else {
                    cout << "Rotated " << Gname << " by " << Grotate << " degrees"<< endl;
                    shapesArray[getShapeIndex(Gname)] -> setRotate(GxLoc);   
                  }
                }
                else {
                    errorSent = 1;
                }
            }

    if(command == "delete"){
    string input;
    int nametook=0;
    lineStream >> input;

    if(lineStream.fail()){
        if(lineStream.eof()){
            cout << "Error: too few arguments" << endl;
            goto come;
        }
        else{
            cout << "Error: invalid argument" << endl;
            goto come;
        }
    }
    if  (  NameTaken(input) == true) {
        nametook = 1;
    }

    if(input != "all" && !nametook){
        cout << "Error: shape "<< input << " not found" << endl;
       goto come;
    }
    while(lineStream.peek() == 32){
        lineStream.ignore(1);
    }
    if(!lineStream.eof()){
        cout << "Error: too many arguments" <<endl;
     goto come;
    }
    if(input == "all"){
         for(int x = 0; x < max_shapes; x++){
            if(shapesArray[x]!=NULL){
                delete shapesArray[x];
                shapesArray[x] = NULL;
            }
        }
        shapeCount=0;
        cout << "Deleted: all shapes" << endl;
        goto come;
    }
    else{
        if(shapesArray[getShapeIndex(input)]!= NULL){
           int i =  getShapeIndex(input);
            delete shapesArray[getShapeIndex(input)];
            shapesArray[i] = NULL;
            cout << "Deleted shape "<< input << endl;
            goto come;
        }
    }
                }
        }
        come: 
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";        // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}
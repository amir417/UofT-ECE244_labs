// ~ece244i/public/exercise 3 parser.exe
//  g++ parser.cpp Shape.cpp -o parser.e
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
Shape** shapesArray = NULL;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;
string nameTop;
string typeTop;
string commandTop;
int xlocTop, ylocTop, xszTop, yszTop, angleTop;

bool foe (stringstream &sin){
    return sin.eof();
}


bool shapeExist (const string& name){
// This function checks if an object with such name exists in the database and if yes, it would 
// pass on the pointer to currentShape.
    for (int i = 0; i < shapeCount; i++)
    {
        if (shapesArray[i] != NULL && name == shapesArray[i]->getName())
        {
        return true;
        }
    }
    return false;
}
int intshapeExist (string& name){
// This function checks if an object with such name exists in the database and if yes, it would 
// pass on the pointer to currentShape. 
    for (int i = 0; i < shapeCount; i++){
        if (shapesArray[i] != NULL && shapesArray[i]->getName() == name)
        {
            return i;
        }
    }
    return 0;
}


void maxShapes (const int& value){
    if (shapesArray != NULL){
        for (int i = 0; i < shapeCount; i++){
            if (shapesArray[i] != NULL){
               delete (shapesArray[i]);
               shapesArray[i] = NULL; 
            }
        }
        delete [] shapesArray;
        shapesArray = NULL;
        shapeCount = 0;
    }
    max_shapes = value;
    shapesArray = new Shape* [max_shapes];
    for (int i = 0; i < max_shapes; i++){
        shapesArray[i] = NULL;
    }
    
    cout << "New database: max shapes is " << max_shapes << endl;
    return;
}

void create (string name, string type, int x_loc, int x_size, int y_loc , int y_size, stringstream &sin){
    while(sin.peek() == 32){
        sin.ignore(1);
    }
    if (shapeExist(name)){
        cout << "Error: shape " << name << " exists"<< endl;
        return;
    }
    else if (!foe(sin)){
        cout << "Error: too many arguments" << endl;
    }
    else if (shapeCount == max_shapes){
        cout << "Error: shape array is full" << endl;
        return;
    }
    else{
        shapesArray [shapeCount] =  new Shape (name, type, x_loc, x_size, y_loc, y_size);
        shapeCount++;
        cout << "Created " << name << ": " << type << " " << x_loc << " " << y_loc << " " << x_size << " " << y_size << endl;
    }
    return;
}

void move ( string name, int x_loc, int y_loc, stringstream &sin){
    while(sin.peek() == 32){
        sin.ignore(1);
    }
        int i;
        if (!shapeExist (name)){
            cout << "Error: shape " << name << " not found" << endl;
            return;
        }
        else if (!foe(sin)){
        cout << "Error: too many arguments" << endl;
        }
        else if (shapeExist (name)){
            i = intshapeExist (name);
            shapesArray[i]->setXlocation(x_loc);
            shapesArray[i]->setYlocation(y_loc);
            cout << "Moved " << name << " to " << shapesArray[i]->getXlocation() << " " << shapesArray[i]->getYlocation() << endl;
        }
    return;
}

void rotate ( string name, int angle, stringstream& sin){
    while(sin.peek() == 32){
        sin.ignore(1);
    }
        int i;
        if (!shapeExist (name)){
            cout << "Error: shape " << name << " not found" << endl;
            return;
        }
        else if (!foe(sin)){
            cout << "Error: too many arguments" << endl;
        }
        else if (shapeExist (name)){
            i = intshapeExist (name);
            shapesArray[i]->setRotate(angle);
            cout << "Rotated " << name << " by " << angle << " degrees" << endl;
        }  
    return;
}

void draw (string name, stringstream& sin){
    while(sin.peek() == 32){
        sin.ignore(1);
    }
    if (!shapeExist (name) && foe(sin)){
        if (name == "all"){
        cout << "Drew all shapes" << endl;
        for (int i = 0; i < shapeCount; i++){
            if (shapesArray[i] != NULL){
                shapesArray[i]->draw();
            } 
        }
        return;
        }
        else {
        cout << "Error: shape " << name << " not found" << endl;
            return;    
        }    
    }
    else if (!shapeExist (name) && name != "all") {
        cout << "Error: shape " << name << " not found" << endl;
            return;    
        }
    else if ( !foe(sin) ){
        cout << "Error: too many arguments" << endl;
    }
    else {
        for (int i = 0; i < shapeCount; i++){
            if (shapesArray[i] != NULL && shapesArray[i]->getName() == name)
            {
                cout <<  "Drew " ;
                shapesArray[i]->draw();
                return;
            }
        }    
    }
    return;
}

void Delete (string name, stringstream& sin){
    while(sin.peek() == 32){
        sin.ignore(1);
    }
    if (!shapeExist (name) && foe(sin)){
        if (name == "all"){
        for (int i = 0; i < shapeCount; i++){
            if (shapesArray[i] != NULL){
                delete (shapesArray[i]);
                shapesArray[i] = NULL;
            }
            
            }
        cout << "Deleted: all shapes" << endl;
        return;
        }
        else {
        cout << "Error: shape " << name << " not found" << endl;
            return;    
        }    
    }
    else if (!shapeExist (name) && name != "all") {
        cout << "Error: shape " << name << " not found" << endl;
            return;    
        }
    else if ( !foe(sin)){
        cout << "Error: too many arguments" << endl;
    }
    else {
        for (int i = 0; i < shapeCount; i++){
            if (shapesArray[i] != NULL && shapesArray[i]->getName() == name){
                delete shapesArray[i];
                shapesArray[i] = NULL;
            }
        }  
        cout << "Deleted shape " << name << endl;  
    }
    return;
}

bool nameCheck (stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    string name;
    sin >> name;
    bool flag = false;

   if (sin.fail()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    for (int i = 0; i < NUM_KEYWORDS; i++){
        if ((commandTop != "draw" && commandTop != "delete") && name == keyWordsList[i])
            flag = true;
    }
    for (int i = 0; i < NUM_TYPES; i++){
        if (name == shapeTypesList[i])
            flag = true;
    }
    if (flag == true) {
        cout << "Error: invalid shape name" << endl;
        return false;
    }
    else if (shapeExist(name) && (commandTop == "create")){
        cout << "Error: shape "<< name << " exists" << endl;
        return false;
    }
    else if (!shapeExist(name) && (commandTop != "create") && name != "all"){
        cout << "Error: shape " << name << " not found" << endl;
        return false;
    }
    else {
        nameTop = name;
        return true;
    }

}

bool typeCheck(stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    string type;
    sin >> type;
    bool flag = false;

    if (sin.fail()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    for (int i = 0; i <NUM_TYPES; i++){
        if (type == shapeTypesList[i]){
            flag = true;
        }
    }
    if (flag == false){
        cout << "Error: invalid shape type" << endl;
        return false;
    }
    else{
        typeTop = type;
        return true;
    }
}

bool xlocCheck(stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    int x;
    sin >> x;
    if (sin.fail() || sin.peek() == '.'){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (x < 0 ){
        cout << "Error: invalid value" << endl;
        return false;
    }
    else {
        xlocTop = x;
        return true;
    }

}

bool xszCheck(stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    int x;
    sin >> x;
    if (sin.fail() || sin.peek() == '.'){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (x < 0 ){
        cout << "Error: invalid value" << endl;
        return false;
    }
    else {
        xszTop = x;
        return true;
    }
}
bool ylocCheck(stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    int y;
    sin >> y;
    if (sin.fail() || sin.peek() == '.'){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (y < 0 ){
        cout << "Error: invalid value" << endl;
        return false;
    }
    else {
        ylocTop = y;
        return true;
    }

}

bool yszCheck(stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    int y;
    sin >> y;
    if (sin.fail() || sin.peek() == '.'){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (y < 0 ){ 
        cout << "Error: invalid value" << endl;
        return false;
    }
    else if (typeTop == "circle" && xszTop != y){
        cout << "Error: invalid value" << endl;
        return false;
    }
    else {
        yszTop = y;
        return true;
    }
}

bool angleCheck (stringstream  &sin){
    if (sin.eof()) {
        cout << "Error: too few arguments" << endl;
        return false;
    }
    int angle;
    sin >> angle;
    if (sin.fail() || sin.peek() == '.'){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (angle < 0 || angle > 360 ){
        cout << "Error: invalid value" << endl;
        return false;
    }
    else {
        angleTop = angle;
        return true;
    }
}

int main() {

    string line;
    
    string name, type;
    int xloc, yloc, xsz, ysz, angle, value;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input
    

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);

        string command;
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command ;
        if (command != "maxShapes" && command != "create" && 
        command != "move" && command != "rotate" && command != "draw" && command != "delete"  ){
                cout << "Error: invalid command" << endl;
        }
        else if (lineStream.peek() == -1){
                    cout << "Error: too few arguments" << endl;
        }
        else{
             if (command == "maxShapes"){
                lineStream >> value;
                if (lineStream.fail() || lineStream.peek() == '.' ){
                    cout << "Error: invalid argument" << endl;
                }
                else if (value < 0){
                    cout<< "Error: invalid value" << endl;
                }
                else if (!lineStream.eof()){
                    cout << "Error: too many arguments" << endl;
                }
                else {maxShapes (value);} 
            }

             else if (command == "create") {
                commandTop = command;
                if (nameCheck (lineStream) && typeCheck (lineStream) && xlocCheck (lineStream) && ylocCheck (lineStream) &&
                xszCheck (lineStream) && yszCheck (lineStream)){
                    create (nameTop, typeTop, xlocTop, xszTop, ylocTop, yszTop, lineStream);
                } 
            }

            else if (command == "move") {
                commandTop = command;
                if (nameCheck (lineStream) && xlocCheck (lineStream) && ylocCheck (lineStream) ){
                    move (nameTop, xlocTop, ylocTop, lineStream);
                }
            }
            else if (command == "rotate"){
                commandTop = command;
                if (nameCheck (lineStream) && angleCheck (lineStream)){
                    rotate (nameTop, angleTop, lineStream);
                }
            }
            else if (command == "draw"){
                commandTop = command;
                if (nameCheck (lineStream) /* && lineStream.eof() */) 
                    { draw (nameTop, lineStream);}
 
            }
            else if (command == "delete"){
                commandTop = command;
                if (nameCheck (lineStream) /* && lineStream.eof() */)
                    { Delete (nameTop, lineStream);}
            }
        } 
            cout << "> ";          // Prompt for input
            getline(cin, line);
        
      // End input loop until EOF.
    
}
    return 0;

}


           









//
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
Shape** shapesArray = NULL;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here


/*void maxShapes(stringstream &ss){

    if(shapeCount != 0){
        for(int j = 0; j < shapeCount; j++){
            delete shapesArray[j];
        }
        delete []shapesArray;
        
    }
    ss >> max_shapes;
    
    if(ss.fail()){

        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }
    }
    else if(max_shapes <= 0){
        cout<< "Error: invalid value" << endl;
        return;
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }

    shapesArray = new Shape*[shapeCount];

    for(int i = 0; i < max_shapes; i++){
            shapesArray[i] = NULL;
    }

    cout << "New database: max shapes is " << max_shapes << endl;
    return;
}
*/

void maxShapes(stringstream &ss){
    int prev_max = max_shapes;
    ss >> max_shapes;

    if(ss.fail()){

        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    else if(max_shapes < 0 ){
        cout<< "Error: invalid value" << endl;
        return;
    }
    while(ss.peek() == 32){
        ss.ignore(1);
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }


    if(shapesArray != NULL){
        for(int j = 0; j < prev_max; j++){
            if (shapesArray[j] != NULL){
             delete shapesArray[j];
            shapesArray[j] = NULL;
            }
        }
        delete []shapesArray;
        shapesArray = NULL;
        shapeCount = 0;
    }

    shapesArray = new Shape*[max_shapes];

    for(int i = 0; i < max_shapes; i++){
            shapesArray[i] = NULL;
    }

    cout << "New database: max shapes is " << max_shapes << endl;
    return;
}

void create(stringstream &ss){

    string name, type;
    int loc_x, loc_y, size_x, size_y;

    ss >> name;

    bool isReserved = 0;
    for (int i = 0; i < 7; i++){
        if(name == keyWordsList[i]){
            isReserved = 1;
        }
    }
    for(int j = 0; j < 4; j++){
        if(name == shapeTypesList[j]){
            isReserved = 1;
        }        
    }

    if(isReserved){
        cout << "Error: invalid shape name" << endl;
        return;
    }

    for(int x = 0; x < shapeCount; x++){
       if(shapesArray[x] != NULL){
            if((shapesArray[x])->getName() == name){
                cout << "Error: shape "<< name<< " exists"<< endl;
                return;
            }
       }
    }
    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    ss >> type;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    bool isTypeValid = 0;

    for(int y = 0; y < 4; y++){
        if(type == shapeTypesList[y]){
            isTypeValid = 1;
        }        
    }
    if(!isTypeValid){
        cout << "Error: invalid shape type" << endl;
        return;
    }


    ss >> loc_x;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    if(loc_x < 0){
        cout << "Error: invalid value" << endl;
        return;
    }

    ss >> loc_y;
    
    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    } 
    if(loc_y < 0 ){
        cout << "Error: invalid value" << endl;
        return;
    }

    ss >> size_x;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    if(size_x < 0 ){
        cout << "Error: invalid value" << endl;
        return;
    }

    ss >> size_y;
    
    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    else if(size_y < 0 ){
        cout << "Error: invalid value" << endl;
        return;
    }
    else if(type == "circle"){
        if(size_x != size_y){
            cout << "Error: invalid value" << endl;
            return;   
        }
    }
    while(ss.peek() == 32){
        ss.ignore(1);
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }
    if(shapeCount == max_shapes){
        cout << "Error: shape array is full" << endl;
        return;
    }

    shapesArray[shapeCount] = new Shape(name, type, loc_x, size_x, loc_y, size_y);
    shapeCount++;

    cout << "Created " << name << ": " << type << " " << loc_x << " " << loc_y << " " << size_x << " " << size_y << endl;

    return;

}

void move_(stringstream &ss){
    string name;
    int x,y, location;
    bool doesNameExist = 0;

    ss >> name;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != NULL){
            if(name == shapesArray[i]->getName()){
                doesNameExist = 1;
                location = i;
            }        
        }
    } 
    if(!doesNameExist){
        cout << "Error: shape "<< name <<  " not found" << endl;
        return;
    }

    ss >> x;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    if(x < 0){
        cout << "Error: invalid value" << endl;
        return;
    }

    ss >> y;
    
    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    if(y < 0){
        cout << "Error: invalid value" << endl;
        return;
    }
    while(ss.peek() == 32){
        ss.ignore(1);
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }

    shapesArray[location]->setXlocation(x);
    shapesArray[location]->setYlocation(y);

    cout << "Moved " << name << " to " << x << " " << y << endl;  

    return;

}

void rotate(stringstream &ss){
    string name;
    int angle,location;
    bool doesNameExist = 0;

    ss >> name;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i]!= NULL){
            if(name == shapesArray[i]->getName()){
              doesNameExist = 1;
              location = i;
           }  
        }      
    } 
    if(!doesNameExist){
        cout << "Error: shape "<< name<<" not found" << endl;
        return;
    }

    ss >> angle;
    
    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    else if(ss.peek() != -1 && ss.peek() != 32){
        cout << "Error: invalid argument" << endl;
        return;   
    }
    if(angle < 0 || angle>360){
        cout << "Error: invalid value" << endl;
        return;
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }

    shapesArray[location]->setRotate(angle);

    cout<< "Rotated " << name << " by "<< angle << " degrees" << endl;

    return;
}

void draw(stringstream &ss){
    string arg;
    bool doesNameExist = 0;
    int location;

    ss >> arg;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != NULL){
            if(arg == shapesArray[i]->getName()){
                doesNameExist = 1;
                location = i;
                break;
            }        
        }
    } 
    if(!doesNameExist && arg != "all"){
        cout << "Error: shape "<<arg<<" not found" << endl;
        return;
    }
        while(ss.peek() == 32){
        ss.ignore(1);
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }
    

    if(arg == "all"){
        cout << "Drew all shapes" << endl;
        if(shapeCount!=0 && shapesArray!= NULL){
        for(int x = 0; x < max_shapes; x++){
            if(shapesArray[x]!= NULL){
                shapesArray[x]->draw();
            }
            //cout <<shapesArray[x]->getName() << ": " << shapesArray[x]->getType() << " " << shapesArray[x]->getXlocation() << " " << shapesArray[x]->getYlocation()<< " " << shapesArray[x]->getXsize()<< " " << shapesArray[x]->getYsize() << endl;
        }
        }
        return;
    }
    else{
        cout<< "Drew ";
        if(shapesArray[location]!= NULL){
                shapesArray[location]->draw();
            }
        //cout << "Drew " << arg << ": " << shapesArray[location]->getType()<< " "<<  shapesArray[location]->getXlocation() << " " << shapesArray[location]->getYlocation()<< " " << shapesArray[location]->getXsize()<< " " << shapesArray[location]->getYsize() << endl;
        return;
    }
    return;
}

void delete_(stringstream &ss){
    string arg;
    bool doesNameExist = 0;
    int location=0;

    ss >> arg;

    if(ss.fail()){
        if(ss.eof()){
            cout << "Error: too few arguments" << endl;
            return;
        }
        else{
            cout << "Error: invalid argument" << endl;
            return;
        }   
    }
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != NULL){
            if(arg == shapesArray[i]->getName()){
                doesNameExist = 1;
                location = i;
                break;
            }        
        }
    } 
    if(!doesNameExist && arg != "all"){
        cout << "Error: shape "<< arg << " not found" << endl;
        return;
    }
    while(ss.peek() == 32){
        ss.ignore(1);
    }
    if(!ss.eof()){
        cout << "Error: too many arguments" <<endl;
        return;
    }
    

    if(arg == "all"){
        
         for(int x = 0; x < max_shapes; x++){
            if(shapesArray[x]!=NULL){
                //cout<<"pass1";
                delete shapesArray[x];
                shapesArray[x] = NULL;
            }
            //cout<<"pass2";
        }
        //delete []shapesArray;
        //cout<<"pass3";
        //shapesArray = NULL;
        shapeCount=0;
        cout << "Deleted: all shapes" << endl;
        return;
    }
    else{
        if(shapesArray!= NULL){
            delete shapesArray[location];
            shapesArray[location] = NULL;
            cout << "Deleted shape "<< arg << endl;
            return;
        }
    }
    return;
}


int main() {

    string line;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        string command;
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        if(command == keyWordsList[1]){
            maxShapes(lineStream);
        }   
        else if(command == keyWordsList[2]){
            create(lineStream);
        } 
        else if(command == keyWordsList[3]){
            move_(lineStream);
        }       
        else if(command == keyWordsList[4]){
            rotate(lineStream);
        } 
        else if(command == keyWordsList[5]){
            draw(lineStream);
        } 
        else if(command == keyWordsList[6]){
            delete_(lineStream);
        } 
        else{
            cout << "Error: invalid command\n";
        }
        
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}


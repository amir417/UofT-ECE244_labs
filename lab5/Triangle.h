//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.

#include "Shape.h"

class Triangle : public Shape {
private:
    float radius;                  // The radius of the circle
    float x1, y1, x2, y2, x3, y3;

public:
    // Constructor
    Triangle (string n,  float x1, float y1, float  x2, float  y2, float x3, float y3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getX1() const;       
    float getX2() const;      
    float getX3() const;       
    float getY1() const;       
    float getY2() const;      
    float getY3() const;      

    // Mutator
    void setX1(float x1);      
    void setX2(float x2);     
    void setX3(float x3);      
    void setY1(float y1);      
    void setY2(float y2);      
    void setY3(float y3);      
    
    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
    virtual float computeArea() const;   // Computes the area of the circle
    
    virtual Shape* clone() const;  // Clones the object
};

#endif /* Triangle_h */





//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

//
//  Circle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

// ***********  ECE244 Student: DO NOT MODIFY THIS FILE  ***********


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build a Circle object
Triangle::Triangle (string n,  float x11, float y11, float  x22, float  y22, float x33, float y33):Shape(n,(x11+x22+x33)/3.0,(y11+y22+y33)/3.0){

    
    x1 = x11;
    y1 = y11;
    x2 = x22;
    y2 = y22;
    x3 = x33;
    y3 = y33;
}

Triangle::~Triangle() {
    // Nothing to do
}

// Accessor
float Triangle::getX1() const {
    return x1;
}
float Triangle::getX2() const {
    return x2;
}
float Triangle::getX3() const {
    return x3;
}
float Triangle::getY1() const {
    return y1;
}
float Triangle::getY2() const {
    return y2;
}
float Triangle::getY3() const {
    return y3;
}

// Mutator
void Triangle::setX1(float r) {
    x1 = r;
}
void Triangle::setX2(float r) {
    x2 = r;
}
void Triangle::setX3(float r) {
    x3 = r;
}
void Triangle::setY1(float r) {
    y1 = r;
}
void Triangle::setY2(float r) {
    y2 = r;
}
void Triangle::setY3(float r) {
    y3 = r;
}


void Triangle:: draw() const{
        cout << std::fixed;
        cout << std::setprecision(2);

         // Print the information
        cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " " <<" " << x2 << " " << " " << y2 << " " <<" " << x3 << " " <<" " << y3 << " " <<computeArea()
         << endl;
    }

float Triangle::computeArea() const {
    // float area, line1, line2, line3, s;
    // line1 = sqrt(pow(y2-y1, 2) + pow(x2-x1, 2));
    // line2 = sqrt(pow(y3-y1, 2) + pow(x3-x1, 2));
    // line3 = sqrt(pow(y2-y3, 2) + pow(x2-x3, 2));

    // s = (line1 + line2 + line3) / 2;
    // area = sqrt(s*(s-line1)*(s-line2)*(s-line3));
    // return (y2);
    return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2))/ 2.0);
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}


#pragma once

#include <string>

using namespace std;

class GroceryItem {
public:
    GroceryItem(string& name, int quantity); //constructor 
    string getName(); //string: getter return name
    int getQuantity(); //int: getter return quantity
    void addItem(); //increment quantity

private:
    string name; //item name
    int quantity; //item quantity
};
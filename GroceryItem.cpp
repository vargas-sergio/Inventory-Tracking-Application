#include "GroceryItem.h"
#include <string>

using namespace std;

//Class Constructor
//@param name - pointer string name of item
//@param quantity - int quantity of item
GroceryItem::GroceryItem(string& name, int quantity) {
    this->name = name;
    this->quantity = quantity;
}

//Name Getter - gets the name of the item
//@returns name - returns private name
string GroceryItem::getName() {
    return name;
}

// Quantity Getter - gets the quantity of the item
//@returns quantity - returns private quantity
int GroceryItem::getQuantity() {
    return quantity;
}

//Add Item - increments the item quantity
void GroceryItem::addItem() {
    quantity++;
}
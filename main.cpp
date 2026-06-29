#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include "GroceryItem.h"

using namespace std;

//save grocery items
map<string, GroceryItem> inventory;

//loads purchase list into memory
//@param filename - item list in text file format
void loadData(const string& fileName) {
    string itemName;
    ifstream inFS(fileName);

    //print error if file cannot be opened
    if (!inFS.is_open()) {
        cout << "Error opening the file -- " << fileName << endl;
        return;
    }
    //loop through file
    while (inFS >> itemName) {
        //normalize inputs
        for (size_t i = 0; i < itemName.size(); i++) {
            itemName[i] = tolower(itemName[i]);
        }
        //increment quantity if item exists
        if (inventory.count(itemName) > 0) {
            inventory.at(itemName).addItem();
        }
        //initialize item if not
        else {
            inventory.emplace(itemName, GroceryItem(itemName, 1));
        }
    }
    //close file
    inFS.close();
}

//create a backup with frequency of items
void createBackup() {
    //open file
    ofstream outFS("frequency.dat");

    //report error if unable to write to file
    if (!outFS.is_open()) {
        cout << "Error could not create file -- frequency.dat" << endl;
        return;
    }
    // export list and print to file
    for (auto& pair : inventory) {
        outFS << pair.second.getName() << " "
            << pair.second.getQuantity() << endl;
    }
    // close file
    outFS.close();
}

//return item count of given item
//@param itemName - name of item in the purchase list
//@returns frequency of item as an integer
int getFrequency(const string& itemName) {
    string name = itemName;

    //normalize input
    for (size_t i = 0; i < name.size(); i++) {
        name[i] = tolower(name[i]);
    }
    // check if item exists
    if (inventory.count(name) > 0) {
        //return 
        return inventory.at(name).getQuantity();
    }
    else {
        // no items
        return 0;
    }

}

//print frequency pairs
void printList() {
    cout << endl;
    cout << " --- Item Frequencies --- " << endl;
    for (auto& pair : inventory) {
        cout << pair.second.getName() << " "; 
        cout << pair.second.getQuantity() << endl;
    }
}

//print histogram
void printHistogram() {
    cout << endl;
    cout <<" --- Purchase Histogram --- " << endl;
    for (auto& pair : inventory) {
        //format width of set
        cout << left << setw(12) << pair.second.getName() ;
        //print # histogram
        for (int i = 0; i < pair.second.getQuantity(); i++) {
            cout << "#";
        }
        cout << endl;
    }
}

int main() {
    int userInput = 0;

    // loop through user options
    while (userInput != 4) {
        // load data and create backup file
        loadData("CS210_Project_Three_Input_File.txt");
        createBackup();

        cout << " ===== Corner Grocer Menu ===== " << endl;
        cout << "1) Search Item Quantity" << endl;
        cout << "2) Print Quantity of Item List" << endl;
        cout << "3) Print Histogram" << endl;
        cout << "4) Exit" << endl << endl;
        cout << "Please select from the choices:";
        cin >> userInput;

        //error message
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Entry: Please try again!" << endl;
            continue;
        }

        switch (userInput) {
        case 1: {
            //return quantity of selected item
            string item;
            cout << "Type item name: ";
            cin >> item;
            int freq = getFrequency(item);
            if (freq == 0) {
                cout << item << " was not found in today's records." << endl;
            }
            else {
                cout << item << " was purchased " << freq << " time(s)." << endl;
            }
            break;
        }
        case 2:
            //print item and quantity lists
            printList();
            break;

        case 3:
            //print item histogram
            printHistogram();
            break;

        case 4:
            //exit program
            cout << "Program Terminated!" << endl;
            break;

        default:
            //default case
            cout << "Invalid Entry: Please try again!" << endl;
            break;
        }
    }

    return 0;
}
#include <iostream>
#include <ctime>
#include <sstream>
#include "Item.h"
#include "Warehouse.h"
#include "Shop.h"
#include "FamilyMart.h"

using namespace std;

int main(){
    FamilyMart* myFamilyMart = FamilyMart::getInstance();
    myFamilyMart->shopInit("shop.txt");
    string instruction;
    while (true){
        cin >> instruction;
        if (instruction == "purchase"){
            string fileName;
            cin >> fileName;
            cin >> fileName;
            if (! myFamilyMart->solvePurchase(fileName)){
                cout <<"No this file"<<endl;
            }
        } else if (instruction == "sell"){
            string fileName;
            cin >> fileName;
            cin >> fileName;
            if (! myFamilyMart->solveSell(fileName)){
                cout << "No this file" <<endl;
            }
        } else if (instruction == "show_sale_amount"){
            cout << myFamilyMart->getSaleAmount() <<endl;
        } else if (instruction == "show_all_shop_name"){
            int shopNumber = myFamilyMart->getShopNumber();
            string * shops = myFamilyMart->getShopName();
            for (int i = 0; i < shopNumber; ++i) {
                cout << shops[i] << endl;
            }
        } else if (instruction == "close"){
            myFamilyMart->close();
            return 0;
        } else {
            cout << "wrong instruction"<< endl;
        }
    }
}

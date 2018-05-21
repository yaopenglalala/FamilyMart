#include <iostream>
#include <ctime>
#include <sstream>
#include "Item.h"
#include "Warehouse.h"
#include "Shop.h"
#include "FamilyMart.h"

using namespace std;

//#define DEBUG
int main(){
#ifdef DEBUG
//    cout << "fdafd" <<endl;
//
//    Item* item = new Item("fads",5.5,5, "fdas");
//
//    //warehouse test
//    Warehouse* warehouse = new Warehouse("Shop test", 1);
//    warehouse->addItem(item);
//    Item* item1 = warehouse->removeItem("fads");
//    cout << "first remove: "<< item1 << endl;
//    Item* item2 = warehouse->removeItem("fads");
//    cout << "second remove: " << item2 << endl;
//    cout << item1->getName() << endl;
//
//    //checksize() correct
//    for (int i = 0; i < 1 ; i ++){
//        Item* item3 = new Item("test", i , i, "2018");
//        warehouse->addItem(item3);
//        cout << item3->getPrice() <<endl;
//    }
//
//    cout << warehouse->checkSize() << endl;
//    delete(warehouse);
//
//    //shop test
//    cout << "----shop test----" << endl;
//    Shop* shop = new Shop("SHOP1");
//    for (int i = 0; i < 10 ; i ++){
//        Item* item3 = new Item("test", i , i, "2018");
//        shop->purchase(item3);
//    }
//    for (int i = 0; i < 25; i++){
//        Item* item3 = new Item("test1", i , i, "2008");
//        shop->purchase(item3);
//    }
//    for (int i = 0; i < 50; i++){
//        Item* item3 = new Item("test2", i , i, "20022");
//        shop->purchase(item3);
//    }
//    for (int i = 0; i < 50; ++i) {
//        shop->sell("test2", 1);
//    }
//    for (int i = 0; i < 25; ++i) {
//        shop->sell("test1", 1);
//    }
//    cout << shop->getSaleAmount() << endl;


    //FamilyMart test
    cout << "----FamilyMart test----" << endl;
    FamilyMart*  myFamilyMart = FamilyMart::getInstance();
  //  myFamilyMart->solvePurchase("fads");
  //  myFamilyMart->solveSell("fas");
  //  myFamilyMart->getSaleAmount();
  //  cout << myFamilyMart->getShopName()[0]<<endl;
    // myFamilyMart->close();

    myFamilyMart->shopInit("shop.txt");
    myFamilyMart->solvePurchase("purchase.txt");
    myFamilyMart->solveSell("sell.txt");
    cout << myFamilyMart->getSaleAmount() << endl;
    cout << myFamilyMart->getShopName()[1] <<endl;
    myFamilyMart->close();
#endif // DEBUG
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

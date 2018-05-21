//
// Created by 妖风 on 2018/5/19.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "FamilyMart.h"
#include "WarehouseUtil.h"
#include "Shop.h"

//#define DEBUG

FamilyMart* FamilyMart::fmInstance = NULL;

FamilyMart::FamilyMart(){
    this->shopList = * new vector<Shop *>;
}

FamilyMart* FamilyMart::getInstance(){
    if (FamilyMart::fmInstance == NULL) {
        FamilyMart::fmInstance = new FamilyMart();
    }
    return FamilyMart::fmInstance;
}

Shop* FamilyMart::newShop(){
    int shopNumber = this->getShopNumber();
    string numberStr;
    stringstream tmpStream;
    tmpStream << (shopNumber + 1);
    tmpStream >> numberStr;

    string shopName = "SHOP" + numberStr;
    Shop* aNewShop = new Shop(shopName);
    this->shopList.push_back(aNewShop);
    return aNewShop;
}

Shop* FamilyMart::newShop(string shopName, int wareSize) {
    Shop* aNewShop = new Shop(shopName, wareSize);
    this->shopList.push_back(aNewShop);
    return aNewShop;
}

void FamilyMart::shopInit(string fileName) {
    ifstream fileinput(fileName);
    string stringLine;
    Shop* treatedShop = NULL;
    if (fileinput.is_open()){//file exists
        while (getline(fileinput, stringLine)){//get line
            stringstream stringLineStream(stringLine);
            string lineHead;
            stringLineStream >> lineHead;
            #ifdef DEBUG
            cout << stringLine <<endl;
            cout << lineHead << endl;
            #endif // DEBUG
            if (lineHead.substr(0, 4) == "SHOP"){
                treatedShop == NULL;

                string shopname = lineHead;
                int totalNumber;
                stringLineStream >> totalNumber;
                for (int i = 0; i < this->shopList.size(); ++i) {
                    if (this->shopList[i]->getName() == shopname){
                        treatedShop = this->shopList[i];
                    }
                }

                if (treatedShop == NULL){
#ifdef DEBUG
cout << lineHead << " " << totalNumber <<endl;
#endif // DEBUG
                    int wareSize = 0;
                    while(totalNumber > WarehouseUtil::getWareSize(wareSize)){
                        wareSize++;
                    }
                    treatedShop = this->newShop(shopname, wareSize);
                }
            } else if (lineHead == "name"){
                continue;
            } else if (lineHead.empty()){
                continue;
            } else {
                stringstream stringStreamItem;
                stringStreamItem << stringLine;
#ifdef DEBUG
                cout << stringLine <<endl;
#endif // DEBUG
                string itemName;
                float  price;
                int lifeDay;
                string productDate;
                stringStreamItem >> itemName >> price >> lifeDay >> productDate;

#ifdef DEBUG
                cout <<"init start: "<< itemName << " " << price << " " << lifeDay <<" "<< productDate<< endl;
#endif
                Item* item = new Item(itemName, price, lifeDay, productDate);
#ifdef DEBUG
                cout << treatedShop << endl;
                cout <<"init: "<< item->getName() << " " << item->getPrice() << " " << item->getLifeDay()<< endl;
#endif
                treatedShop->purchase(item);
            }
        }
    }

    fileinput.close();
}

bool FamilyMart::solvePurchase(string fileName){
#ifdef DEBUG
    cout << fileName << endl;
//    for (int i = 0; i < 75; i++){
//        Item* item3 = new Item("test1", i , i, "20000");
//        this->shopList[0]->purchase(item3);
//    }
#endif
    ifstream fileinput(fileName);
    string stringLine;
    string lineHead;
    Shop* treatedShop = this->shopList[0];
    if (fileinput.is_open()){//file exists
        while (getline(fileinput, stringLine)){//get line
#ifdef DEBUG
            cout << stringLine << endl;
#endif
            stringstream stringLineStream;
            stringLineStream << stringLine;
            stringLineStream >> lineHead;
#ifdef DEBUG
            cout <<"linehead : " <<lineHead << endl;
#endif
            if (lineHead == "PURCHASE"){
                int totalNumber;
                string shopname;
                stringLineStream >> totalNumber;
                stringLineStream >> shopname;
                for (int i = 0; i < this->shopList.size(); ++i) {
                    if (this->shopList[i]->getName() == shopname){
                        treatedShop = this->shopList[i];
                        treatedShop->changeSize(totalNumber);
                    }
                }
            } else if (lineHead == "name"){
                stringLineStream.clear();
            } else if (lineHead.empty()){
                stringLineStream.clear();
            } else {
                string itemName = lineHead;
                float  price;
                int lifeDay;
                string productDate;
                stringLineStream >> price >> lifeDay >> productDate;
                Item* item = new Item(itemName, price, lifeDay, productDate);
#ifdef DEBUG
                cout <<"purchase: "<< item->getName() << " " << item->getPrice() << endl;
#endif
                treatedShop->purchase(item);
            }
        }
    } else {
        return false;
    }

    fileinput.close();
    return true;
}

bool FamilyMart::solveSell(string fileName){
#ifdef DEBUG
//    for (int i = 0; i < 25; i++){
//        this->shopList[0]->sell("test1",1);
//    }
#endif
    ifstream fileinput(fileName);
    string stringLine;
    Shop* treatedShop = this->shopList[0];
    float discount = 1;
    if (fileinput.is_open()){//file exists
        while (getline(fileinput, stringLine)){//get line
#ifdef DEBUG
            cout << stringLine << endl;
#endif
            stringstream stringLineStream;
            string lineHead;
            stringLineStream << stringLine;
            stringLineStream >> lineHead;
#ifdef DEBUG
 //           cout <<"linehead : " <<lineHead << endl;
#endif
            if (lineHead.substr(0, 4) == "SALE"){
                string discountString;
                string shopname;
                stringLineStream >> discountString >> shopname;
                if (shopname.empty()){
                    discount = 1;
                    shopname = discountString;
                } else {
                    stringstream tmp(discountString);
                    tmp >> discount;
                }
                for (int i = 0; i < this->shopList.size(); ++i) {
                    if (this->shopList[i]->getName() == shopname){
                        treatedShop = this->shopList[i];
                    }
                }
            } else if (lineHead.empty()){
                continue;
            } else {
                treatedShop->sell(lineHead, discount);
                treatedShop->changeSize(-1);
#ifdef DEBUG
                cout << this->shopList.size() << endl;
#endif
                if (this->getSaleAmount() >= (55 * this->shopList.size())){
                    this->newShop();
                }
            }
        }
    } else return false;

    fileinput.close();
    return true;
}

float FamilyMart::getSaleAmount() const{
    float saleAmount = 0;
    size_t shopNumber = this->shopList.size();
    for (size_t i = 0; i < shopNumber; i++) {
        saleAmount += shopList[i]->getSaleAmount();
    }
#ifdef DEBUG
    cout << saleAmount << endl;
#endif
    return saleAmount;
}

int FamilyMart::getShopNumber() const{
    return static_cast<int>(this->shopList.size());
}

string* FamilyMart::getShopName() const{
    size_t shopNumber = this->shopList.size();
    string* shopNames = new string[shopNumber] ;
    for (size_t i = 0; i < shopNumber; i++) {
        shopNames[i] = shopList[i]->getName();
    }
    return shopNames;
}

void FamilyMart::close() {
#ifdef DEBUG
    cout << "Family mart close" <<endl;
#endif
    size_t shopNumber = this->shopList.size();
    for (int i = 0; i < shopNumber; ++i) {
        shopList[i]->shopClose();
        delete shopList[i];
    }
}

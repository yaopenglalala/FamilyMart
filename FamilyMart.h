//
// Created by 妖风 on 2018/5/19.
//

#ifndef FAMILYMART_FAMILYMART_H
#define FAMILYMART_FAMILYMART_H

#include "Shop.h"

class FamilyMart{
    static FamilyMart* fmInstance;
    vector<Shop *> shopList;
    FamilyMart ();
    FamilyMart (FamilyMart &);
public:
    static FamilyMart* getInstance();

    Shop* newShop();
    Shop* newShop(string shopName, int wareSize);
    void shopInit(string fileName);
    bool solvePurchase(string fileName);
    bool solveSell(string fileName);
    float getSaleAmount() const ;
    int getShopNumber() const ;
    string* getShopName() const ;
    void close();
};


#endif //FAMILYMART_FAMILYMART_H

//
// Created by 妖风 on 2018/5/19.
//

#ifndef FAMILYMART_ITEM_H
#define FAMILYMART_ITEM_H

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Item{
    string name;
    float price;
    int lifeDay;
    string productDate;
public :
    Item (string name, float price, int lifeDay, string productDate);
    string getName() const ;
    float getPrice() const ;
    int getLifeDay() const ;
    string getProDate() const ;
};

#endif //FAMILYMART_ITEM_H

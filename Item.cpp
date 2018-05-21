#include <iostream>
#include <ctime>
#include "Item.h"

using namespace std;

Item::Item(string name, float price, int lifeDay, string productDate){
    this->name = name;
    this->price = price;
    this->lifeDay = lifeDay;
    this->productDate = productDate;
}

string Item::getName() const{
    return this->name;
}

float Item::getPrice() const{
    return this->price;
}

int Item::getLifeDay() const{
    return this->lifeDay;
}

string Item::getProDate() const{
    return this->productDate;
}



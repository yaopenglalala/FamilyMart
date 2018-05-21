//
// Created by 妖风 on 2018/5/19.
//

#ifndef FAMILYMART_SHOP_H
#define FAMILYMART_SHOP_H

#include "Item.h"
#include "Warehouse.h"

class Shop{
    string name;
    Warehouse* warehouse;
    float saleAmount;

    bool warehouseAdjustable();
public:
    Shop (string shopName);
    Shop (string shopname, int wareSize);
    string getName() const;
    float getSaleAmount() const;
    bool purchase(Item* item);
    bool sell(string itemName, float discount);
    bool changeSize(int addItemNumber);
    void shopClose();
};

#endif //FAMILYMART_SHOP_H

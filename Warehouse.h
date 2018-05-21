//
// Created by 妖风 on 2018/5/19.
//

#ifndef FAMILYMART_WAREHOUSE_H
#define FAMILYMART_WAREHOUSE_H

#include "Item.h"
#include <map>
#include <queue>

class Warehouse{
    map <string, queue<Item *>> productsMap;
    string shopName;
    int sizelevel;
public :
    Warehouse(string shopName, int sizelevel = 0);
    ~Warehouse();

    int getItemNumber();
    int getSize() const;

    /*
    0: everything is ok;
    1: it should be smaller
    2: it should be larger
    3: it should be larger but no larger
    */
    int checkSize();

    map <string, queue<Item *>> * getAllItems();
    void setAllItem(map <string, queue<Item *>> * allItems);
    void addItem(Item* item);
    Item* removeItem(string itemName);//todo:check the return
    void cleanWarehouse();
};

#endif //FAMILYMART_WAREHOUSE_H

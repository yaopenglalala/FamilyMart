#include <map>
#include "Item.h"
#include "Warehouse.h"
#include "WarehouseUtil.h"

using namespace std;

Warehouse::Warehouse(string shopName, int sizelevel){
    this->productsMap = *(new map<string, queue<Item *>>);
    this->shopName = shopName;
    this->sizelevel = sizelevel;
    cout <<"shop name: "<< this->shopName << ", warehouse size: " << WarehouseUtil::getWareSize(this->sizelevel) << " constructor is invoked!" <<endl;
}

Warehouse::~Warehouse() {
    cout <<"shop name: "<< this->shopName << ", warehouse size: " << WarehouseUtil::getWareSize(this->sizelevel) << " deconstructor is invoked!" <<endl;
}

/*
get the amount of items in warehouse
*/
int Warehouse::getItemNumber(){
    int itemNumber = 0;
    map<string, queue<Item *>>::iterator it;
    it = this->productsMap.begin();
    while (it != this->productsMap.end()) {
        itemNumber += it->second.size();
        it ++;
    }
    return itemNumber;
}

/*
get warehouse size level
*/
int Warehouse::getSize() const{
    return this->sizelevel;
}

/*
get items to transport
*/
map <string, queue<Item *>> * Warehouse::getAllItems(){
    return &(this->productsMap);
}

/*
using transport to set items
*/
void Warehouse::setAllItem(map <string, queue<Item *>> * allItems){
    this->productsMap = *allItems;
}


/*
add new item
*/
void Warehouse::addItem(Item *item){
    map<string, queue<Item *>>::iterator resIt = this->productsMap.find(item->getName());
    if (resIt != productsMap.end()) {
        queue<Item *> *itemList = &resIt->second;
        itemList->push(item);
    } else {
        queue<Item *> *newItemList = new queue<Item *>;
        newItemList->push(item);
        this->productsMap.insert(pair<string, queue<Item *>>(item->getName(), *newItemList));
    }
}


/*
remove item
*/
Item* Warehouse::removeItem(string itemName){
    map<string, queue<Item *>>::iterator resIt = this->productsMap.find(itemName);
    if (resIt != this->productsMap.end()) {
        queue<Item *>* itemList = &(resIt->second);
        if (itemList->size() > 0){
            Item* resItem = itemList->front();
            itemList->pop();
            return resItem;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}


/*
close shop and destroy the warehouse
*/
void Warehouse::cleanWarehouse(){
    map<string, queue<Item *>>::iterator it;
    it = this->productsMap.begin();
    while (it != this->productsMap.end()) {
        queue<Item *> list= it->second;
        size_t size = list.size();
        for (size_t i = 0; i < size; ++i) {
            Item * tmp = list.front();
            list.pop();
            delete tmp;
        }
        it ++;
    }
}


#include <map>
#include "Item.h"
#include "Warehouse.h"
#include "WarehouseUtil.h"

//#define DEBUG
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

int Warehouse::getItemNumber(){
    int itemNumber = 0;
    map<string, queue<Item *>>::iterator it;
    it = this->productsMap.begin();
    while (it != this->productsMap.end()) {
#ifdef DEBUG
        cout << "list " << it->first << " "<<it->second.size() << endl;
#endif
        itemNumber += it->second.size();
        it ++;
    }
    return itemNumber;
}

int Warehouse::getSize() const{
    return this->sizelevel;
}

int Warehouse::checkSize(){
    int itemNumber = this->getItemNumber();
#ifdef DEBUG
    cout <<"items number: "<< itemNumber << endl;
#endif
    if (itemNumber >= WarehouseUtil::getWareSize(this->sizelevel)){
        if (this->sizelevel >= (WarehouseUtil::wareSizeLevels() - 1)){
            return 3;
        } else return 2;
    } else if (this->sizelevel > 0 && itemNumber <= WarehouseUtil::getWareSize(this->sizelevel - 1)){
        return 1;
    } else return 0;
}

map <string, queue<Item *>> * Warehouse::getAllItems(){
    return &(this->productsMap);
}

void Warehouse::setAllItem(map <string, queue<Item *>> * allItems){
    this->productsMap = *allItems;
}

void Warehouse::addItem(Item *item){
#ifdef DEBUG
    cout << "add: " <<item->getName() << " "<< item << endl;
#endif
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

Item* Warehouse::removeItem(string itemName){
    map<string, queue<Item *>>::iterator resIt = this->productsMap.find(itemName);
    if (resIt != this->productsMap.end()) {
#ifdef DEBUG
        cout << "remove: find " << itemName << endl;
#endif
        queue<Item *>* itemList = &(resIt->second);
        if (itemList->size() > 0){
            Item* resItem = itemList->front();
            itemList->pop();
#ifdef DEBUG
            cout << "remove: " << resItem<< endl;
#endif
            return resItem;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

void Warehouse::cleanWarehouse(){
#ifdef DEBUG
    cout << "warehouse close" << endl;
#endif
    map<string, queue<Item *>>::iterator it;
    it = this->productsMap.begin();
    while (it != this->productsMap.end()) {
        queue<Item *> list= it->second;
        size_t size = list.size();
        for (int i = 0; i < size; ++i) {
            Item * tmp = list.front();
            list.pop();
            delete tmp;
        }
        it ++;
    }
}


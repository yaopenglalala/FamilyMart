#include "Shop.h"
#include "WarehouseUtil.h"

Shop::Shop(string shopname){
    this->name = shopname;
    this->warehouse = NULL;
    this->saleAmount = 0;
}

Shop::Shop(string shopname, int wareSize){
    this->name = shopname;
    this->warehouse = new Warehouse(this->getName(), wareSize);
    this->saleAmount = 0;
}

string Shop::getName() const{
    return this->name;
}

float Shop::getSaleAmount()const {
    return saleAmount;
}

bool Shop::purchase(Item* item){
    if (this->warehouse == NULL) this->warehouse = new Warehouse(this->name);
    this->warehouse->addItem(item);
    return true;
}

bool Shop::sell(string itemName, float discount){
    Item* resItem = this->warehouse->removeItem(itemName);
    if (resItem != NULL) {
        this->saleAmount += resItem->getPrice() * discount;
        delete resItem;
        return true;
    } else return false;
}

bool Shop::changeSize(int addNewItem){
    int oldItemNumber = this->warehouse->getItemNumber();
    int newItemNumber = oldItemNumber + addNewItem;
    if (newItemNumber >= WarehouseUtil::getWareSize(this->warehouse->getSize())){
        if (this->warehouse->getSize() >= (WarehouseUtil::wareSizeLevels() - 1)){
            return false;
        } else {
            Warehouse* newWarehouse = new Warehouse(this->name, this->warehouse->getSize() + 1);
            WarehouseUtil::transport(this->warehouse, newWarehouse);
            this->warehouse = newWarehouse;
            return true;
        }
    } else if (this->warehouse->getSize() > 0 && newItemNumber <= WarehouseUtil::getWareSize(this->warehouse->getSize() - 1)){
            Warehouse* newWarehouse = new Warehouse(this->name, this->warehouse->getSize() - 1);
            WarehouseUtil::transport(this->warehouse, newWarehouse);
            this->warehouse = newWarehouse;
            return true;
    } else return true;
}

void Shop::shopClose() {
    if (warehouse == NULL) {
        cout << "shop name: " << this->getName() << ", no warehouse!"<<endl;
    } else {
        this->warehouse->cleanWarehouse();
        delete this->warehouse;
    }
}

//
// Created by 妖风 on 2018/5/19.
//

#ifndef FAMILYMART_WAREHOUSEUTIL_H
#define FAMILYMART_WAREHOUSEUTIL_H
#include "Warehouse.h"

class WarehouseUtil{
    static const int sizelevels;
    static int sizelist[];
public:
    static int wareSizeLevels();
    static int getWareSize(int sizelevel);
    static void transport(Warehouse *startWare, Warehouse *endWare);
};

#endif //FAMILYMART_WAREHOUSEUTIL_H

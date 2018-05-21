#include "WarehouseUtil.h"

const int WarehouseUtil::sizelevels = 3;
int WarehouseUtil::sizelist[WarehouseUtil::sizelevels] = {25, 50, 100};

int WarehouseUtil::wareSizeLevels(){
    return WarehouseUtil::sizelevels;
}

int WarehouseUtil::getWareSize(int sizelevel){
    return WarehouseUtil::sizelist[sizelevel];
}

void WarehouseUtil::transport(Warehouse *startWare, Warehouse *endWare){
    endWare->setAllItem(startWare->getAllItems());
    delete startWare;
}




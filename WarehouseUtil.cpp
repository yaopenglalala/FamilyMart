#include "WarehouseUtil.h"

const int WarehouseUtil::sizelevels = 3;
int WarehouseUtil::sizelist[WarehouseUtil::sizelevels] = {25, 50, 100};

/*
return the levels number of warehouse sizes
*/
int WarehouseUtil::wareSizeLevels(){
    return WarehouseUtil::sizelevels;
}

//return the size of a certain size level
int WarehouseUtil::getWareSize(int sizelevel){
    return WarehouseUtil::sizelist[sizelevel];
}

//transport warehouse
void WarehouseUtil::transport(Warehouse *startWare, Warehouse *endWare){
    endWare->setAllItem(startWare->getAllItems());
    delete startWare;
}




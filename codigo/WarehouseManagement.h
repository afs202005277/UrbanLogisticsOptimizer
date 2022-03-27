#ifndef PROJETO1_WAREHOUSEMANAGEMENT_H
#define PROJETO1_WAREHOUSEMANAGEMENT_H
#include <vector>
#include "Courier.h"
#include "TransportRequest.h"

class WarehouseManagement {
private:
    std::vector<Courier> couriers;
    std::vector<TransportRequest> transportRequests;
};


#endif //PROJETO1_WAREHOUSEMANAGEMENT_H

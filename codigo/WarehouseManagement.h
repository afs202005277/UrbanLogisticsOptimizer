#ifndef PROJETO1_WAREHOUSEMANAGEMENT_H
#define PROJETO1_WAREHOUSEMANAGEMENT_H
#include <vector>
#include "Courier.h"
#include "TransportTypes.h"

class WarehouseManagement {
private:
    std::vector<Courier> couriers;
    std::vector<NormalTransport> normalTransports;
    std::vector<ExpressTransport> expressTransports;
    std::vector<Courier> readCourierData(const std::string &couriersData) const;
    std::vector<Courier> readTransportsData(const std::string &transportsData) const;
public:
    WarehouseManagement(const std::string &couriersData, const std::string &transportsData);
};


#endif //PROJETO1_WAREHOUSEMANAGEMENT_H

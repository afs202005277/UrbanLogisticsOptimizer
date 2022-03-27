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
    std::vector<NormalTransport> readNormalTransportsData(const std::string &input) const;
    std::vector<ExpressTransport> readExpressTransportsData(const std::string &input) const;
public:
    WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                        const std::string &expressTransportsData);
};


#endif //PROJETO1_WAREHOUSEMANAGEMENT_H

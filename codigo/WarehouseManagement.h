#ifndef PROJETO1_WAREHOUSEMANAGEMENT_H
#define PROJETO1_WAREHOUSEMANAGEMENT_H
#include <vector>
#include "Courier.h"
#include "TransportTypes.h"

class WarehouseManagement {
private:
    unsigned int minimumWeight = INT_MAX;
    unsigned int minimumVolume = INT_MAX;
    unsigned int notAssignedNormalPackages;
    std::vector<Courier> couriers;
    std::vector<NormalTransport> normalTransports;
    std::vector<ExpressTransport> expressTransports;

    static std::vector<Courier> readCourierData(const std::string &couriersData) ;
    std::vector<NormalTransport> readNormalTransportsData(const std::string &input);
    static std::vector<ExpressTransport> readExpressTransportsData(const std::string &input) ;
public:
    WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                        const std::string &expressTransportsData);

    unsigned int optimizeNormalPackagesDistribution();

    unsigned int knapsack(Courier &courier);

    static bool canCarry(const Courier& courier, NormalTransport package);
};


#endif //PROJETO1_WAREHOUSEMANAGEMENT_H

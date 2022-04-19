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

    static std::vector<Courier> readCourierData(const std::string &couriersData);
    std::vector<NormalTransport> readNormalTransportsData(const std::string &input);
    static std::vector<ExpressTransport> readExpressTransportsData(const std::string &input);
    static bool sortCouriersByRatio(const Courier &c1, const Courier &c2);
    static bool sortCouriersByNumberPackages(const Courier &c1, const Courier &c2);
    static bool sortNormalTransportByRatio(const NormalTransport &n1, const NormalTransport &n2);
    static bool sortNormalTransportByPriority(const NormalTransport &n1, const NormalTransport &n2);
    static bool canCarry(const Courier& courier, NormalTransport package);
    unsigned int knapsack(Courier &courier);
    void prioritizeUnsignedPackages();

public:
    WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                        const std::string &expressTransportsData);

    unsigned int optimizeNormalPackagesDistribution();

    int optimizeProfit();

    void resetElements();

    double optimizeExpressTransports();

    double getOperationEfficiency();

    bool changeCourierAvailability(const std::string &licensePlate, bool available);

    void distributePackages();

    unsigned int amountOfCouriersAvailable();

    unsigned int getUsedCouriers();

    std::pair<unsigned int, unsigned int> minAndMaxNumPackagesOfCouriers();

    int numNormalTransportPackages();

    bool addNormalTransportPackages(const std::string &input);

    void endOfBusiness();
};


#endif //PROJETO1_WAREHOUSEMANAGEMENT_H

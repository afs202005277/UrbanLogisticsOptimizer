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

    /**
    * Reads courier's data from the given file and returns a vector of Couriers with the information from the file
    * @param couriersData data file location
    * @return vector of the couriers existing in the the file
    */
    static std::vector<Courier> readCourierData(const std::string &couriersData);

    /**
    * Reads Normal Transport data from the given file and returns a vector of Normal Transport with the file information
    * @param input data file location
    * @return Normal Transport vector with the information from the file
    */
    std::vector<NormalTransport> readNormalTransportsData(const std::string &input);

    /**
    * Reads Express Transport data from the given file and returns a vector of Express Transport with the file information
    * @param input data file location
    * @return Express Transport vector with the information from the file
    */
    static std::vector<ExpressTransport> readExpressTransportsData(const std::string &input);

    /**
    * Auxiliary function to use when sorting Couriers by their ratio.
    * @return Returns true if c1 ratio is greater than c2 and false otherwise.
    */
    static bool sortCouriersByRatio(const Courier &c1, const Courier &c2);

    /**
    * Auxiliary function to use when sorting Couriers by the amount of packages they are carrying.
    * @return Returns true if the number of packages assigned to c1 is smaller than c2 and false otherwise.
    */
    static bool sortCouriersByNumberPackages(const Courier &c1, const Courier &c2);

    /**
    * Auxiliary function to use when sorting Normal Transports by ratio.
    * @return Returns true if n1 priority is greater than n2 or, if equal, returns true if n1 ratio is greater than n2 and false otherwise.
    */
    static bool sortNormalTransportByRatio(const NormalTransport &n1, const NormalTransport &n2);

    /**
    * Auxiliary function to use when sorting Normal Transports by priority.
    * @return Returns true if n1 priority is higher than n2 and false otherwise.
    */
    static bool sortNormalTransportByPriority(const NormalTransport &n1, const NormalTransport &n2);

    /**
    * Checks if a given courier can carry a given package.
    * @param courier
    * @param package
    * @return Returns true if the courier can carry the package, false otherwise.
    */
    static bool canCarry(const Courier& courier, NormalTransport package);

    /**
    * Function that aims to fill the given courier to its maximum capacity.
    * This is a special version of a knapsack problem since the variables that we want to maximize are also the constraints.
    * @param courier
    * @return Number of packages assigned to the courier.
    */
    unsigned int courierFiller(Courier &courier);


    /**
    * Increments the priority of the normal packages that were not assigned to a courier.
    */
    void prioritizeUnsignedPackages();

    /**
    * Sets assigned variable to false, on all normal packages.
    * Removes the priority on all normal packages.
    * Sets the current volume and weight to 0 on all couriers.
    * Clears the deliveries vector of the couriers.
    */
    void resetElements();

public:
    WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                        const std::string &expressTransportsData);

    /**
    * Scenario 1: Function that optimizes the packages in order to minimize the use of couriers.
    * Takes use of courierFiller function.
    * @return Number of used Couriers
    */
    unsigned int optimizeNormalPackagesDistribution();

    /**
    * Scenario 2: Function that maximizes the company profit for a given day. Takes use of the courierFiller function.
    * @return Returns the profit.
    */
    int optimizeProfit();

    /**
    * Scenario 3: Function that minimizes the mean time of deliveries in a day.
    * @return Returns the mean time.
    */
    double optimizeExpressTransports();

    /**
    * Calculates the quotient between the number of normal packages assigned and the total number of normal packages.
    * @return Returns the quotient.
    */
    double getOperationEfficiency();

    /**
    * Changes the availability of a given courier. Changing availability means that the courier will not be used in the different scenarios.
    * @param licensePlate identifies the Courier.
    * @param available defines availability.
    * @return Returns true if successful (the courier exists) and false otherwise.
    */
    bool changeCourierAvailability(const std::string &licensePlate, bool available);

    /**
    * Balances the number of deliveries by courier.
    */
    void distributePackages();

    /**
     * Counts the number of couriers that are available.
     * @return number of available couriers.
     */
    unsigned int amountOfCouriersAvailable();

    /**
     * Counts the number of couriers that are currently in use (carrying packages)
     * @return the number of couriers that are currently in use (carrying packages)
     */
    unsigned int getUsedCouriers();

    /**
     * Calculates the minimum and maximum number of packages being carried by a courier
     * @return a pair with the minimum (first value of the pair) and the maximum value (second value of the pair)
     */
    std::pair<unsigned int, unsigned int> minAndMaxNumPackagesOfCouriers();

    /**
     * Returns the number of existing normal packages.
     * @return amount of existing normal packages.
     */
    unsigned int numNormalTransportPackages();

    /**
    * Adds new packages to the normalTransport vector.
    * @param input The name of the normal transports file.
    * @return Returns true if successful and false otherwise.
    */
    bool addNormalTransportPackages(const std::string &input);

    /**
     * Clears the deliveries vector of each courier and sets the pesoAtual and volAtual variables to 0.
     * Prioritizes normal packages that were not assigned during that day.
     * Erases the normal packages that were already assigned.
     */
    void endOfBusiness();
};


#endif //PROJETO1_WAREHOUSEMANAGEMENT_H

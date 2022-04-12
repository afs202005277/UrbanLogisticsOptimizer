#include "WarehouseManagement.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;


WarehouseManagement::WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                                         const std::string &expressTransportsData) {
    couriers = readCourierData(couriersData);
    normalTransports = readNormalTransportsData(normalTransportsData);
    expressTransports = readExpressTransportsData(expressTransportsData);
    notAssignedNormalPackages = normalTransports.size();
}

/**
 * Reads courier data from the given file and returns a vector of Couriers with the file information
 * @param couriersData data file location
 * @return Courier vector with file data
 */
vector<Courier> WarehouseManagement::readCourierData(const string &couriersData) {
    vector<Courier> res;
    ifstream input(couriersData);
    string line;
    getline(input, line);
    while(!input.eof()){
        unsigned int volMax, pesoMax, custo;
        string plate;
        input >> volMax >> pesoMax >> custo >> plate;
        res.emplace_back(Courier(plate, volMax, pesoMax, custo));
    }
    input.close();
    return res;
}

/**
 * Reads Normal Transport data from the given file and returns a vector of Normal Transport with the file information
 * @param input data file location
 * @return Normal Transport vector with file data
 */
std::vector<NormalTransport> WarehouseManagement::readNormalTransportsData(const string &input) {
    vector<NormalTransport> res;
    ifstream data(input);
    string line;
    getline(data, line);
    while(!data.eof()){
        unsigned int volume, peso, recompensa;
        data >> volume >> peso >> recompensa;
        res.emplace_back(NormalTransport{peso, volume, recompensa, false, peso * 5000000 + volume, (double) (recompensa*recompensa) / (volume * peso), 0});
        if (peso < minimumWeight)
            minimumWeight = peso;
        if (volume < minimumVolume)
            minimumVolume = volume;
    }
    data.close();
    return res;
}

/**
 * Reads Express Transport data from the given file and returns a vector of Express Transport with the file information
 * @param input data file location
 * @return Express Transport vector with file data
 */
std::vector<ExpressTransport> WarehouseManagement::readExpressTransportsData(const string &input) {
    vector<ExpressTransport> res;
    ifstream data(input);
    string line;
    getline(data, line);
    while(!data.eof()){
        unsigned int volume, peso, recompensa, tempo;
        data >> volume >> peso >> recompensa >> tempo;
        res.emplace_back(ExpressTransport{peso, volume, recompensa, tempo});
    }
    data.close();
    return res;
}

/**
 * Scenario 1: Function that optimizes the packages in order to minimize the use of couriers. Takes use of knapsack function.
 * @return Number of used Couriers
 */
unsigned int WarehouseManagement::optimizeNormalPackagesDistribution() {
    sort(couriers.begin(), couriers.end(), greater<>());
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByPriority);
    unsigned int courierIdx = 0, usedCouriers = 0;
    while(notAssignedNormalPackages > 0 && courierIdx < couriers.size()){
        unsigned int packagesAssigned = knapsack(couriers[courierIdx]);
        if (packagesAssigned != 0) {
            notAssignedNormalPackages -= packagesAssigned;
            usedCouriers++;
        }
        courierIdx++;
    }
    prioritizeUnsignedPackages();
    return usedCouriers;
}

/**
 * Auxiliary function to use in sort().
 * @return Returns true if n1 priority is higher than n2 and false otherwise.
 */
bool WarehouseManagement::sortNormalTransportByPriority(const NormalTransport &n1, const NormalTransport &n2) {
    return n1.priority > n2.priority;
}

/**
 * Function that aims to solve the knapsack problem. In this case, the knapsack is a Courier and we pretend to distribute packages.
 * @param courier
 * @return Number of packages the courier is carrying.
 */
unsigned int WarehouseManagement::knapsack(Courier &courier) {
    if (!courier.isAvailable()){
        return 0;
    }
    unsigned int max = 0;
    if (courier.getPesoAtual() + minimumWeight >= courier.getPesoMax() || courier.getVolAtual() + minimumVolume >= courier.getVolMax())
        return courier.getNumDeliveries();
    for (NormalTransport &package:normalTransports){
        if (canCarry(courier, package) && !package.assigned){
            package.assigned = true;
            courier.addPackage(package);
            unsigned int current = knapsack(courier);
            if (current > max){
                max = current;
            } else {
                package.assigned = false;
                courier.removePackage(package);
            }
        }
    }
    return courier.getNumDeliveries();
}

/**
 * Checks if Courier can carry package.
 * @param courier
 * @param package
 * @return Returns if the Courier can carry package.
 */
bool WarehouseManagement::canCarry(const Courier& courier, NormalTransport package) {
    return courier.getPesoAtual() + package.weight <= courier.getPesoMax() && courier.getVolAtual() + package.volume <= courier.getVolMax();
}

/**
 * Increments the priority of unsigned packages.
 */
void WarehouseManagement::prioritizeUnsignedPackages() {
    for (NormalTransport &a : normalTransports) {
        if (!a.assigned) {
            a.priority++;
        }
    }
}

/**
 * Scenario 2: Function thay maximizes the company profit for a given day. Takes use of knapsack function.
 * @return Returns the profit.
 */
int WarehouseManagement::optimizeProfit() {
    sort(couriers.begin(), couriers.end(), sortCouriersByRatio);
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByRatio);

    unsigned int courierIdx = 0, expenses=0;
    while(notAssignedNormalPackages > 0 && courierIdx < couriers.size()){
        unsigned int packagesAssigned = knapsack(couriers[courierIdx]);
        if (packagesAssigned != 0) {
            notAssignedNormalPackages -= packagesAssigned;
            expenses += couriers[courierIdx].getTransportFee();
        }
        courierIdx++;
    }
    unsigned int revenue=0;
    for (auto &package:normalTransports){
        revenue += package.payment;
    }
    prioritizeUnsignedPackages();
    return (int) (revenue - expenses);
}

/**
 * Calculates percentage of delivered packages.
 * @return Returns the pergentage.
 */
double WarehouseManagement::getOperationEfficiency() {
    unsigned int deliveredProducts = normalTransports.size() - notAssignedNormalPackages;
    return deliveredProducts / (double) normalTransports.size();
}

/**
 * Auxiliary function to use in sort().
 * @return Returns true if c1 ratio is higher than c2 and false otherwise.
 */
bool WarehouseManagement::sortCouriersByRatio(const Courier &c1, const Courier &c2) {
    return c1.getRatio() > c2.getRatio();
}

/**
 * Auxiliary function to use in sort().
 * @return Returns true if n1 ratio is higher than n2 and false otherwise.
 */
bool WarehouseManagement::sortNormalTransportByRatio(const NormalTransport &n1, const NormalTransport &n2) {
    return n1.priority == n2.priority ? n1.ratio > n2.ratio : n1.priority > n2.priority;
}

/**
 * Resets elements: sets assigned variable to false on all packages and sets current volume and weight to 0 on all couriers.
 */
void WarehouseManagement::resetElements() {
    for (auto &package:normalTransports)
        package.assigned = false;

    for (auto &courier:couriers) {
        vector<NormalTransport> tmp;
        courier.setDeliveries(tmp);
        courier.setPesoAtual(0);
        courier.setVolAtual(0);
    }

    notAssignedNormalPackages = normalTransports.size();
}

/**
 * Scenario 3: Function that minimizes the mean time of deliveries in a day.
 * @return Returns the mean time.
 */
double WarehouseManagement::optimizeExpressTransports() {
    sort(expressTransports.begin(), expressTransports.end());
    unsigned int sum=0, total=0;
    for (auto i:expressTransports){
        sum += i.timeToDelivery;
        total += sum;
    }
    return total / (double) expressTransports.size();
}

/**
 * Changes Courier's availability. Changing availability means that the courier will not be used in the different scenarios.
 * @param licensePlate identifies the Courier.
 * @param available defines availability.
 * @return Returns true if successful and false otherwise.
 */
bool WarehouseManagement::changeCourierAvailability(const std::string &licensePlate, bool available) {
    for (auto & courier : couriers){
        if (courier.getLicensePlate() == licensePlate){
            courier.setAvailable(available);
            return true;
        }
    }
    return false;
}

/**
 * Balances the number of deliveries by courier
 */
void WarehouseManagement::distributePackages() {
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByRatio);

    for(auto deliverie : normalTransports) {
        sort(couriers.begin(), couriers.end(), sortCouriersByNumberPackages);
        for (auto &courier : couriers) {
            if (canCarry(courier, deliverie)){
                courier.addPackage(deliverie);
                break;
            }
        }
    }

    // This shouldn't be here
    for(auto courier : couriers){
        std::cout << courier.getNumDeliveries() << "\n";
    }
}

/**
 * Auxiliary function to use in sort().
 * @return Returns true if the number of packages assigned to c1 is smaller than c2 and false otherwise.
 */
bool WarehouseManagement::sortCouriersByNumberPackages(const Courier &c1, const Courier &c2) {
    return c1.getNumDeliveries() < c2.getNumDeliveries();
}

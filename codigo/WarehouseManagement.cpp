#include "WarehouseManagement.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const unsigned int maxTimeWindow = 8 * 3600; // 8 hours converted into seconds

WarehouseManagement::WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                                         const std::string &expressTransportsData) {
    couriers = readCourierData(couriersData);
    normalTransports = readNormalTransportsData(normalTransportsData);
    expressTransports = readExpressTransportsData(expressTransportsData);
    notAssignedNormalPackages = normalTransports.size();
}


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

std::vector<NormalTransport> WarehouseManagement::readNormalTransportsData(const string &input) {
    vector<NormalTransport> res;
    ifstream data(input);
    string line;
    getline(data, line);
    while(!data.eof()){
        unsigned int volume, peso, recompensa;
        data >> volume >> peso >> recompensa;
        res.emplace_back(NormalTransport{peso, volume, recompensa, false, (double) (recompensa*recompensa) / (volume * peso), 0});
        if (peso < minimumWeight)
            minimumWeight = peso;
        if (volume < minimumVolume)
            minimumVolume = volume;
    }
    data.close();
    return res;
}


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


unsigned int WarehouseManagement::optimizeNormalPackagesDistribution() {
    resetElements();
    sort(couriers.begin(), couriers.end(), greater<>());
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByPriority);
    unsigned int courierIdx = 0, usedCouriers = 0;
    while(notAssignedNormalPackages > 0 && courierIdx < couriers.size()){
        unsigned int packagesAssigned = courierFiller(couriers[courierIdx]);
        if (packagesAssigned != 0) {
            notAssignedNormalPackages -= packagesAssigned;
            usedCouriers++;
        }
        courierIdx++;
    }

    return usedCouriers;
}

bool WarehouseManagement::sortNormalTransportByPriority(const NormalTransport &n1, const NormalTransport &n2) {
    return n1.priority > n2.priority;
}

unsigned int WarehouseManagement::courierFiller(Courier &courier) {
    if (!courier.isAvailable()){
        return 0;
    }
    unsigned int max = 0;
    if (courier.getPesoAtual() + minimumWeight >= courier.getPesoMax() || courier.getVolAtual() + minimumVolume >= courier.getVolMax())
        return courier.getNumDeliveries();
    for (NormalTransport &package:normalTransports) {
        if (canCarry(courier, package) && !package.assigned) {
            package.assigned = true;
            courier.addPackage(package);
            unsigned int current = courierFiller(courier);
            if (current > max) {
                max = current;
            } else {
                package.assigned = false;
                courier.removePackage(package);
            }
        }
    }
    return courier.getNumDeliveries();
}

bool WarehouseManagement::canCarry(const Courier& courier, NormalTransport package) {
    return courier.getPesoAtual() + package.weight <= courier.getPesoMax() && courier.getVolAtual() + package.volume <= courier.getVolMax();
}


void WarehouseManagement::prioritizeUnsignedPackages() {
    for (NormalTransport &a : normalTransports) {
        if (!a.assigned) {
            a.priority++;
        }
    }
}

int WarehouseManagement::optimizeProfit() {
    resetElements();
    sort(couriers.begin(), couriers.end(), sortCouriersByRatio);
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByRatio);

    unsigned int courierIdx = 0, expenses=0;
    while(notAssignedNormalPackages > 0 && courierIdx < couriers.size()){
        unsigned int packagesAssigned = courierFiller(couriers[courierIdx]);
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

    return (int) (revenue - expenses);
}

double WarehouseManagement::getOperationEfficiency() {
    unsigned int deliveredProducts = normalTransports.size() - notAssignedNormalPackages;
    return deliveredProducts / (double) normalTransports.size();
}

bool WarehouseManagement::sortCouriersByRatio(const Courier &c1, const Courier &c2) {
    return c1.getRatio() > c2.getRatio();
}

bool WarehouseManagement::sortNormalTransportByRatio(const NormalTransport &n1, const NormalTransport &n2) {
    return n1.priority == n2.priority ? n1.ratio > n2.ratio : n1.priority > n2.priority;
}


void WarehouseManagement::resetElements() {
    for (auto &package:normalTransports){
        package.assigned = false;
    }

    for (auto &courier:couriers) {
        vector<NormalTransport> tmp;
        courier.setDeliveries(tmp);
        courier.setPesoAtual(0);
        courier.setVolAtual(0);
    }

    notAssignedNormalPackages = normalTransports.size();
}

double WarehouseManagement::optimizeExpressTransports() {
    sort(expressTransports.begin(), expressTransports.end());
    unsigned int sum=0, total=0;
    for (auto i:expressTransports){
        if (sum + i.timeToDelivery > maxTimeWindow)
            break;
        sum += i.timeToDelivery;

        total += sum;
    }
    return total / (double) expressTransports.size();
}


bool WarehouseManagement::changeCourierAvailability(const std::string &licensePlate, bool available) {
    for (auto & courier : couriers){
        if (courier.getLicensePlate() == licensePlate){
            courier.setAvailable(available);
            return true;
        }
    }
    return false;
}


void WarehouseManagement::distributePackages() {
    resetElements();
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByPriority);

    for(auto &deliveries: normalTransports) {
        for (auto &courier : couriers) {
            if (canCarry(courier, deliveries)){
                notAssignedNormalPackages--;
                courier.addPackage(deliveries); deliveries.assigned = true;
                sort(couriers.begin(), couriers.end(), sortCouriersByNumberPackages);
                break;
            }
        }
    }
}


bool WarehouseManagement::sortCouriersByNumberPackages(const Courier &c1, const Courier &c2) {
    return c1.getNumDeliveries() < c2.getNumDeliveries();
}

unsigned int WarehouseManagement::amountOfCouriersAvailable() {
    unsigned int c=0;
    for (const auto& courier:couriers){
        if (courier.isAvailable())
            c++;
    }
    return c;
}

unsigned int WarehouseManagement::getUsedCouriers() {
    unsigned int c=0;
    for (const auto& courier:couriers){
        if (courier.getNumDeliveries() != 0)
            c++;
    }
    return c;
}

std::pair<unsigned int, unsigned int> WarehouseManagement::minAndMaxNumPackagesOfCouriers() {
    unsigned int max = 0, min = -1;
    for (const auto& courier:couriers){
        if (courier.getNumDeliveries() > max)
            max = courier.getNumDeliveries();
        if (courier.getNumDeliveries() < min)
            min = courier.getNumDeliveries();
    }
    return {min, max};
}


bool WarehouseManagement::addNormalTransportPackages(const std::string &input) {
    std::vector<NormalTransport> newPackages = readNormalTransportsData(input);
    if(newPackages.empty())
        return false;

    normalTransports.insert(normalTransports.end(), newPackages.begin(), newPackages.end());

    return true;
}

unsigned int WarehouseManagement::numNormalTransportPackages() {
    return normalTransports.size();
}

void WarehouseManagement::endOfBusiness() {
    for (auto &courier : couriers){
        courier.eraseDeliveries();
    }

    prioritizeUnsignedPackages();

    normalTransports.erase(std::remove_if(normalTransports.begin(),
                              normalTransports.end(),
                              [](NormalTransport package){return package.assigned;}),
                           normalTransports.end());
}

#include "WarehouseManagement.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

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
        res.emplace_back(NormalTransport{peso, volume, recompensa, false, peso * 5000000 + volume, (volume * peso) / (double) recompensa});
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
    sort(couriers.begin(), couriers.end(), greater<Courier>());
    unsigned int courierIdx = 0, usedCouriers = 0;
    while(notAssignedNormalPackages > 0 && courierIdx < couriers.size()){
        unsigned int packagesAssigned = knapsack(couriers[courierIdx]);
        if (packagesAssigned != 0) {
            notAssignedNormalPackages -= packagesAssigned;
            usedCouriers++;
        }
        courierIdx++;
    }
    return usedCouriers;
}

unsigned int WarehouseManagement::knapsack(Courier &courier) {
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

bool WarehouseManagement::canCarry(const Courier& courier, NormalTransport package) {
    return courier.getPesoAtual() + package.weight <= courier.getPesoMax() && courier.getVolAtual() + package.volume <= courier.getVolMax();
}



int WarehouseManagement::optimizeProfit() {
    sort(couriers.begin(), couriers.end(), sortCouriersByRatio);
    sort(normalTransports.begin(), normalTransports.end(), sortNormalTransportByRatio);

    unsigned int courierIdx = 0, usedCouriers = 0, expenses=0;
    while(notAssignedNormalPackages > 0 && courierIdx < couriers.size()){
        unsigned int packagesAssigned = knapsack(couriers[courierIdx]);
        if (packagesAssigned != 0) {
            notAssignedNormalPackages -= packagesAssigned;
            expenses += couriers[courierIdx].getTransportFee();
            usedCouriers++;
        }
        courierIdx++;
    }
    unsigned int revenue=0;
    for (auto &package:normalTransports){
        revenue += package.payment;
    }
    return revenue - expenses;
}

bool WarehouseManagement::sortCouriersByRatio(const Courier &c1, const Courier &c2) {
    return c1.getRatio() > c2.getRatio();
}

bool WarehouseManagement::sortNormalTransportByRatio(const NormalTransport &n1, const NormalTransport &n2) {
    return n1.ratio < n2.ratio;
}

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

double WarehouseManagement::optimizeExpressTransports() {
    sort(expressTransports.begin(), expressTransports.end());
    unsigned int sum=0, total=0;
    for (auto i:expressTransports){
        sum += i.timeToDelivery;
        total += sum;
    }
    return total / (double) expressTransports.size();
}
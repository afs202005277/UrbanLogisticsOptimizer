#include "Courier.h"
#include <iostream>
#include <utility>
using namespace std;

Courier::Courier(std::string licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee) : licensePlate(std::move(
        licensePlate)), volMax(volMax), pesoMax(pesoMax), transportFee(transportFee) {}

bool Courier::operator<(const Courier &rhs) const {
    if (volMax < rhs.volMax)
        return true;
    if (volMax == rhs.volMax && pesoMax < rhs.pesoMax)
        return true;
    return false;
}

bool Courier::operator>(const Courier &rhs) const {
    return rhs < *this;
}

bool Courier::operator<=(const Courier &rhs) const {
    return !(rhs < *this);
}

bool Courier::operator>=(const Courier &rhs) const {
    return !(*this < rhs);
}

unsigned int Courier::getVolMax() const {
    return volMax;
}

unsigned int Courier::getVolAtual() const {
    return volAtual;
}

unsigned int Courier::getPesoMax() const {
    return pesoMax;
}

unsigned int Courier::getPesoAtual() const {
    return pesoAtual;
}

void Courier::addPackage(NormalTransport package) {
    pesoAtual += package.weight;
    volAtual += package.volume;
    deliveries.push_back(package);
}

void Courier::removePackage(NormalTransport package) {
    pesoAtual -= package.weight;
    volAtual -= package.volume;
    for (int i=0;i<deliveries.size();i++){
        if (package == deliveries[i]){
            deliveries.erase(deliveries.begin() + i);
            break;
        }
    }
}

unsigned int Courier::getNumDeliveries() const {
    return deliveries.size();
}

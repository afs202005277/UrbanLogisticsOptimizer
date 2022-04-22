#include "Courier.h"
using namespace std;

Courier::Courier(std::string licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee) : licensePlate(std::move(
        licensePlate)), volMax(volMax), pesoMax(pesoMax), transportFee(transportFee) {
    ratio = (volMax * pesoMax) / (double) (transportFee*transportFee);
    available = true;
}


bool Courier::operator<(const Courier &rhs) const {
    if (volMax < rhs.volMax)
        return true;
    if (volMax == rhs.volMax && pesoMax < rhs.pesoMax)
        return true;
    return false;
}

/**
 * Courier is considered more than another if it's maximum volume is more than the other courier and if equal, the maximum weight is used for the comparison.
 * @param rhs
 * @return True if considered more and false otherwise.
 */
bool Courier::operator>(const Courier &rhs) const {
    return rhs < *this;
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


double Courier::getRatio() const {
    return ratio;
}


void Courier::setDeliveries(const vector<NormalTransport> &deliveries) {
    Courier::deliveries = deliveries;
}


void Courier::setVolAtual(unsigned int volAtual) {
    Courier::volAtual = volAtual;
}


void Courier::setPesoAtual(unsigned int pesoAtual) {
    Courier::pesoAtual = pesoAtual;
}


unsigned int Courier::getTransportFee() const {
    return transportFee;
}


bool Courier::isAvailable() const {
    return available;
}


void Courier::setAvailable(bool available) {
    Courier::available = available;
}


const string &Courier::getLicensePlate() const {
    return licensePlate;
}

void Courier::eraseDeliveries() {
    this->deliveries.clear();
    pesoAtual = 0;
    volAtual = 0;
}

bool operator==(const Courier &lhs, const Courier &rhs) {
    return lhs.licensePlate == rhs.licensePlate;
}



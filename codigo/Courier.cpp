#include "Courier.h"
using namespace std;

Courier::Courier(std::string licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee) : licensePlate(std::move(
        licensePlate)), volMax(volMax), pesoMax(pesoMax), transportFee(transportFee) {
    ratio = (volMax * pesoMax) / (double) (transportFee*transportFee);
    available = true;
}

/**
 * Courier is considered less than another if it's maximum volume is less than the other courier and if equal, the maximum weight is used for the comparison.
 * @param rhs
 * @return True if considered less and false otherwise.
 */
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

/**
 * Gets Courier's maximum volume.
 * @return Returns the maximum volume.
 */
unsigned int Courier::getVolMax() const {
    return volMax;
}

/**
 * Gets Courier's current volume.
 * @return Returns the current volume.
 */
unsigned int Courier::getVolAtual() const {
    return volAtual;
}

/**
 * Gets Courier's maximum weight.
 * @return Returns the maximum weight.
 */
unsigned int Courier::getPesoMax() const {
    return pesoMax;
}

/**
 * Gets Courier's current weight.
 * @return Returns the current weight.
 */
unsigned int Courier::getPesoAtual() const {
    return pesoAtual;
}

/**
 * Adds a package to Courier's deliveries list.
 * @param package
 */
void Courier::addPackage(NormalTransport package) {
    pesoAtual += package.weight;
    volAtual += package.volume;
    deliveries.push_back(package);
}

/**
 * Removes a package from Courier's deliveries list.
 * @param package
 */
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

/**
 * Gets Courier's current deliveries amount.
 * @return Returns the current deliveries amount.
 */
unsigned int Courier::getNumDeliveries() const {
    return deliveries.size();
}

/**
 * Gets Courier's ratio.
 * @return Returns the Courier's ratio.
 */
double Courier::getRatio() const {
    return ratio;
}

/**
 * Sets Courier's deliveries variable.
 * @param deliveries
 */
void Courier::setDeliveries(const vector<NormalTransport> &deliveries) {
    Courier::deliveries = deliveries;
}

/**
 * Sets Courier's current volume.
 * @param volAtual
 */
void Courier::setVolAtual(unsigned int volAtual) {
    Courier::volAtual = volAtual;
}

/**
 * Sets Courier's current weight.
 * @param pesoAtual
 */
void Courier::setPesoAtual(unsigned int pesoAtual) {
    Courier::pesoAtual = pesoAtual;
}

/**
 * Gets Courier's transport fee.
 * @return Returns the transport fee.
 */
unsigned int Courier::getTransportFee() const {
    return transportFee;
}

/**
 * Checks if Courier is available for deliveries.
 * @return Returns true if available and false otherwise.
 */
bool Courier::isAvailable() const {
    return available;
}

/**
 * Sets Courier's availability.
 * @param available
 */
void Courier::setAvailable(bool available) {
    Courier::available = available;
}

/**
 * Gets Courier's license plate.
 * @return Returns the license plate.
 */
const string &Courier::getLicensePlate() const {
    return licensePlate;
}

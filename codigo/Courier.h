#ifndef PROJETO1_COURIER_H
#define PROJETO1_COURIER_H

#include <string>
#include <vector>
#include "TransportTypes.h"

class Courier {
private:
    std::string licensePlate;
    unsigned int volMax, volAtual=0;
    unsigned int pesoMax, pesoAtual=0;
    unsigned int transportFee;
    std::vector<NormalTransport> deliveries;
public:
    bool operator<(const Courier &rhs) const;

    bool operator>(const Courier &rhs) const;

    bool operator<=(const Courier &rhs) const;

    bool operator>=(const Courier &rhs) const;

public:
    Courier(std::string licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee);

    unsigned int getNumDeliveries() const;

    unsigned int getVolMax() const;

    unsigned int getVolAtual() const;

    unsigned int getPesoMax() const;

    unsigned int getPesoAtual() const;

    void addPackage(NormalTransport package);

    void removePackage(NormalTransport package);
};


#endif //PROJETO1_COURIER_H

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
    double ratio;
    bool available;
public:
    bool operator<(const Courier &rhs) const;

    bool operator>(const Courier &rhs) const;

    bool operator<=(const Courier &rhs) const;

    bool operator>=(const Courier &rhs) const;

    Courier(std::string licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee);

    unsigned int getNumDeliveries() const;

    unsigned int getVolMax() const;

    unsigned int getVolAtual() const;

    unsigned int getPesoMax() const;

    unsigned int getPesoAtual() const;

    void addPackage(NormalTransport package);

    void removePackage(NormalTransport package);

    double getRatio() const;

    void setDeliveries(const std::vector<NormalTransport> &deliveries);

    void setVolAtual(unsigned int volAtual);

    void setPesoAtual(unsigned int pesoAtual);

    unsigned int getTransportFee() const;

    bool isAvailable() const;

    void setAvailable(bool available);

    const std::string &getLicensePlate() const;
};


#endif //PROJETO1_COURIER_H

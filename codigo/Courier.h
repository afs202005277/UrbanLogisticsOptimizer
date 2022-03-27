#ifndef PROJETO1_COURIER_H
#define PROJETO1_COURIER_H

#include <string>

class Courier {
private:
    std::string licensePlate;
    unsigned int volMax;
    unsigned int pesoMax;
    unsigned int transportFee;
public:
    Courier(const std::string &licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee);
};


#endif //PROJETO1_COURIER_H

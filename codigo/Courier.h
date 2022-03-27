#ifndef PROJETO1_COURIER_H
#define PROJETO1_COURIER_H

#include <string>

class Courier {
private:
    std::string licensePlate;
    double volMax;
    double pesoMax;
    double transportFee;
public:
    Courier(const std::string &licensePlate, double volMax, double pesoMax, double transportFee);
};


#endif //PROJETO1_COURIER_H

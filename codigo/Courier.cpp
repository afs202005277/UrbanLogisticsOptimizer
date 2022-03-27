#include "Courier.h"

Courier::Courier(const std::string &licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee) : licensePlate(
        licensePlate), volMax(volMax), pesoMax(pesoMax), transportFee(transportFee) {}

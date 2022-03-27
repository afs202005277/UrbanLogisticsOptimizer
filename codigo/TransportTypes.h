#ifndef PROJETO1_TRANSPORTTYPES_H
#define PROJETO1_TRANSPORTTYPES_H
struct NormalTransport{
    double weight;
    double volume;
    double payment;
};

struct ExpressTransport{
    double weight;
    double volume;
    double payment;
    int timeToDelivery;
};

#endif //PROJETO1_TRANSPORTTYPES_H

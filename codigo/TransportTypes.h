#ifndef PROJETO1_TRANSPORTTYPES_H
#define PROJETO1_TRANSPORTTYPES_H
struct NormalTransport{
    unsigned int weight;
    unsigned int volume;
    unsigned int payment;
};

struct ExpressTransport{
    unsigned int weight;
    unsigned int volume;
    unsigned int payment;
    unsigned int timeToDelivery;
};

#endif //PROJETO1_TRANSPORTTYPES_H

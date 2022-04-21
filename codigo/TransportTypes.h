#ifndef PROJETO1_TRANSPORTTYPES_H
#define PROJETO1_TRANSPORTTYPES_H

struct NormalTransport{
    unsigned int weight;
    unsigned int volume;
    unsigned int payment;
    bool assigned;
    double ratio;
    unsigned int priority;

    bool operator==(const NormalTransport &rhs) const {
        return weight == rhs.weight &&
               volume == rhs.volume &&
               payment == rhs.payment &&
               assigned == rhs.assigned &&
               ratio == rhs.ratio;
    }
};

struct ExpressTransport{
    unsigned int weight;
    unsigned int volume;
    unsigned int payment;
    unsigned int timeToDelivery;

    bool operator<(const ExpressTransport &rhs) const {
        return timeToDelivery < rhs.timeToDelivery;
    }
};

#endif //PROJETO1_TRANSPORTTYPES_H

#ifndef PROJETO1_TRANSPORTTYPES_H
#define PROJETO1_TRANSPORTTYPES_H
struct NormalTransport{
    unsigned int weight;
    unsigned int volume;
    unsigned int payment;
    bool assigned;
    unsigned int combinedStorage;
    double ratio;

    friend bool operator==(const NormalTransport &lhs, const NormalTransport &rhs) {
        return lhs.weight == rhs.weight &&
               lhs.volume == rhs.volume &&
               lhs.payment == rhs.payment &&
               lhs.assigned == rhs.assigned;
    }

    friend bool operator!=(const NormalTransport &lhs, const NormalTransport &rhs) {
        return !(rhs == lhs);
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

    bool operator>(const ExpressTransport &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const ExpressTransport &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const ExpressTransport &rhs) const {
        return !(*this < rhs);
    }
};

#endif //PROJETO1_TRANSPORTTYPES_H

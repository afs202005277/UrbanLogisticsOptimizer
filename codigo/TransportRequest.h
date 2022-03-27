#ifndef PROJETO1_TRANSPORTREQUEST_H
#define PROJETO1_TRANSPORTREQUEST_H

enum TransportType {normal, expresso};
class TransportRequest {
private:
    TransportType transportType;
    double weight;
    double volume;
    double payment;
public:
    TransportRequest(TransportType transportType, double weight, double volume, double payment);
};


#endif //PROJETO1_TRANSPORTREQUEST_H

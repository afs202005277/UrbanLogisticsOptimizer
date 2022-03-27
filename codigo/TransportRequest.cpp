#include "TransportRequest.h"

TransportRequest::TransportRequest(TransportType transportType, double weight, double volume, double payment)
        : transportType(transportType), weight(weight), volume(volume), payment(payment) {}

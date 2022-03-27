#include "WarehouseManagement.h"
#include <fstream>
#include <string>

using namespace std;

WarehouseManagement::WarehouseManagement(const std::string &couriersData, const std::string &normalTransportsData,
                                         const std::string &expressTransportsData) {
    couriers = readCourierData(couriersData);
    normalTransports = readNormalTransportsData(normalTransportsData);
    expressTransports = readExpressTransportsData(expressTransportsData);
}

vector<Courier> WarehouseManagement::readCourierData(const string &couriersData) const {
    vector<Courier> res;
    ifstream input(couriersData);
    string line;
    getline(input, line);
    input.ignore();
    while(!input.eof()){
        unsigned int volMax, pesoMax, custo;
        string plate;
        input >> volMax >> pesoMax >> custo >> plate;
        res.emplace_back(Courier(plate, volMax, pesoMax, custo));
    }
    input.close();
    return res;
}

std::vector<NormalTransport> WarehouseManagement::readNormalTransportsData(const string &input) const {
    vector<NormalTransport> res;
    ifstream data(input);
    string line;
    getline(data, line);
    data.ignore();
    while(!data.eof()){
        unsigned int volume, peso, recompensa;
        data >> volume >> peso >> recompensa;
        res.emplace_back(NormalTransport{peso, volume, recompensa});
    }
    data.close();
    return res;
}

std::vector<ExpressTransport> WarehouseManagement::readExpressTransportsData(const string &input) const {
    vector<ExpressTransport> res;
    ifstream data(input);
    string line;
    getline(data, line);
    data.ignore();
    while(!data.eof()){
        unsigned int volume, peso, recompensa, tempo;
        data >> volume >> peso >> recompensa >> tempo;
        res.emplace_back(ExpressTransport{peso, volume, recompensa, tempo});
    }
    data.close();
    return res;
}

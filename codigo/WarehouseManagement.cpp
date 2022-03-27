#include "WarehouseManagement.h"
#include <fstream>
#include <string>

using namespace std;

WarehouseManagement::WarehouseManagement(const string &couriersData, const string &transportsData) {
    couriers = readCourierData(couriersData);
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

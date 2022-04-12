#include <iostream>
#include <chrono>
#include "WarehouseManagement.h"
#include "NormalPackageGenerator.h"
#include "CourierGenerator.h"
#include <fstream>
using namespace std;



int main() {
    /*NormalPackageGenerator normalPackageGenerator("../input/normalTransports.txt", 440);
    normalPackageGenerator.generate();
    CourierGenerator courierGenerator("../input/carrinhas.txt", 50);
    courierGenerator.generate();*/
    ofstream output("output.txt");
    for (auto numNormal:NormalPackageGenerator::amountNormalPackages){
        for (auto numCouriers:CourierGenerator::amountCouriers){
            string courierInput = "../input/generated/couriers/" + to_string(numCouriers) + ".txt";
            string normalTransportsInput = "../input/generated/normalPackages/" + to_string(numNormal) + ".txt";
            string expressTransportsInput = "../input/cenario21_encomendas.txt";
            WarehouseManagement warehouseManagement(courierInput, normalTransportsInput, expressTransportsInput);
            output << numCouriers << " couriers and " << numNormal << " normal packages." << endl;

            auto start = chrono::steady_clock::now();
            unsigned int couriersUsed = warehouseManagement.optimizeNormalPackagesDistribution();
            auto end = chrono::steady_clock::now();
            output << "Optimize normal transport: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
            warehouseManagement.resetElements();
            start = chrono::steady_clock::now();
            unsigned int profit = warehouseManagement.optimizeProfit();
            end = chrono::steady_clock::now();
            output << "Optimize profit: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl << endl;
        }
    }

    /*
    string courierInput = "../input/generated/couriers/" + to_string(64) + ".txt";
    string normalTransportsInput = "../input/generated/normalPackages/" + to_string(16000) + ".txt";
    string expressTransportsInput = "../input/cenario21_encomendas.txt";
    WarehouseManagement warehouseManagement(courierInput, normalTransportsInput, expressTransportsInput);
    output << 8 << " couriers and " << 8 << " normal packages." << endl;

    warehouseManagement.distributePackages();
    */

    return 0;
}

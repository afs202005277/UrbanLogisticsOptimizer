#include <iostream>
#include "WarehouseManagement.h"
using namespace std;

int main() {
    WarehouseManagement warehouseManagement("../input/cenario21_carrinhas.txt", "../input/cenario21_encomendas.txt", "../input/cenario21_encomendas.txt");
    cout << warehouseManagement.optimizeNormalPackagesDistribution() << endl;
    warehouseManagement.resetElements();
    cout << warehouseManagement.optimizeProfit() << endl;
    warehouseManagement.resetElements();
    cout << warehouseManagement.optimizeExpressTransports() << endl;
    return 0;
}

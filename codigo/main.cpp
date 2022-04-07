#include <iostream>
#include "WarehouseManagement.h"
#include "NormalPackageGenerator.h"
#include "CourierGenerator.h"
using namespace std;



int main() {
    /*NormalPackageGenerator normalPackageGenerator("../input/normalTransports.txt", 440);
    normalPackageGenerator.generate();*/
    CourierGenerator courierGenerator("../input/carrinhas.txt", 50);
    courierGenerator.generate();

    /*WarehouseManagement warehouseManagement("../input/cenario21_carrinhas.txt", "../input/cenario21_encomendas.txt", "../input/cenario21_encomendas.txt");
    cout << warehouseManagement.optimizeNormalPackagesDistribution() << endl;

    warehouseManagement.resetElements();
    cout << warehouseManagement.optimizeProfit() << endl;

    warehouseManagement.resetElements();
    cout << warehouseManagement.optimizeExpressTransports() << endl;*/
    return 0;
}

#include <iostream>
#include "WarehouseManagement.h"
#include "NormalPackageGenerator.h"
using namespace std;

void fileNameReader(string &defaultCourierPath, string &defaultNormalTransports, string &defaultExpressTransports){
    string tmp;
    cout << "Insert the name of the couriers file: ";
    getline(cin, tmp);
    if (!tmp.empty())
        defaultCourierPath = "../input/" + tmp;

    cout << endl << "Insert the name of the normal transports file: ";
    getline(cin, tmp);
    if (!tmp.empty())
        defaultNormalTransports = "../input/" + tmp;

    cout << endl << "Insert the name of the express transports file: ";
    getline(cin, tmp);
    if (!tmp.empty())
        defaultExpressTransports = "../input/" + tmp;
}

void optionChooser(WarehouseManagement &warehouseManagement){
    int optionInt;
    cout << "Which algorithm do you want to run?" << endl;
    cout << "1: optimizeNormalPackagesDistribution: distribute the normal packages using the least amount of couriers" << endl;
    cout << "2: optimizeProfit: distribute the normal packages so that the profit is maximized" << endl;
    cout << "3: optimizeExpressTransports: distribute the express packages so that the average time of delivery is minimized" << endl;
    cout << "4: getOperationEfficiency: returns the quotient between the number of normal packages delivered and the total number of normal packages received" << endl;
    cout << "5: changeCourierAvailability: the couriers may be unavailable, so this method is used to set the availability (boolean) of a given courier." << endl;
    cout << "6: distributePackages: distributes the packages that were assigned to the couriers, so that the number of packages assigned to each of the couriers is more balanced." << endl;
    cout << "7: addNormalTransportPackages: adds new normal transport packages to be delivered." << endl;
    cout << "8: endOfBusiness: Mark the end of the working day" << endl;
    cout << "Choose an option: ";
    string option;
    getline(cin, option);
    optionInt = stoi(option);
    cout << endl;
    string licensePlate, availability, fileName;
    pair<unsigned int, unsigned int> minMax;
    switch (optionInt) {
        case 1:
            cout << "The app used " << warehouseManagement.optimizeNormalPackagesDistribution() << " of the " << warehouseManagement.amountOfCouriersAvailable() << " couriers that were available." << endl;
            break;
        case 2:
            cout << "The maximum profit was " << warehouseManagement.optimizeProfit() << " using " << warehouseManagement.getUsedCouriers() << " couriers." << endl;
            break;
        case 3:
            cout << "The average time of delivery was " << warehouseManagement.optimizeExpressTransports() << "." << endl;
            break;
        case 4:
            cout << "The operation efficiency was " << warehouseManagement.getOperationEfficiency() << "." << endl;
            break;
        case 5:
            cout << "What is the license plate of the courier? ";
            getline(cin, licensePlate);
            cout << "Is the courier available? (y/n) ";
            getline(cin, availability);
            if (toupper(availability[0]) == 'Y')
                warehouseManagement.changeCourierAvailability(licensePlate, true);
            else if (toupper(availability[0]) == 'N')
                warehouseManagement.changeCourierAvailability(licensePlate, false);
            break;
        case 6:
            minMax = warehouseManagement.minAndMaxNumPackagesOfCouriers();
            cout << "Before calling the function, the courier carrying the smallest number of packages, was carrying " << minMax.first << "." << endl;
            cout << "The one with the greatest amount of packages, was carrying " << minMax.second << "." << endl;
            warehouseManagement.distributePackages();
            minMax = warehouseManagement.minAndMaxNumPackagesOfCouriers();
            cout << "After calling the function, the minimum is " << minMax.first << "." << endl;
            cout << "And the maximum is " << minMax.second << "." << endl;
            break;
        case 7:
            cout << "Insert the name of the normal transports file: ";
            getline(cin, fileName);
            if (!fileName.empty())
                fileName = "../input/" + fileName;
            cout << "Before calling the function, the number of normal transport packages to be delivered is " << warehouseManagement.numNormalTransportPackages() << "." << endl;
            if(warehouseManagement.addNormalTransportPackages(fileName))
                cout << "After calling the function, the number of packages is " << warehouseManagement.numNormalTransportPackages() << "." << endl;
            else
                cout << "The selected file doesn't exist." << endl;
            break;
        case 8:
            warehouseManagement.endOfBusiness();
            cout << warehouseManagement.numNormalTransportPackages() << " to be delivered." << endl;
            break;
        default:
            cout << "Option out of bounds!" << endl;
    }
}

int main() {
    string defaultCourierPath = "../input/carrinhas.txt";
    string defaultNormalTransports = "../input/normalTransports.txt";
    string defaultExpressTransports = "../input/expressTransports.txt";
    cout << "Welcome to our package management app!" << endl;
    fileNameReader(defaultCourierPath, defaultNormalTransports, defaultExpressTransports);
    WarehouseManagement warehouseManagement(defaultCourierPath, defaultNormalTransports, defaultExpressTransports);

    string option;
    do{
        optionChooser(warehouseManagement);
        cout << "Do you want to make more operations? (y/n) ";
        getline(cin, option);
    } while(toupper(option[0]) == 'Y');

    return 0;
}

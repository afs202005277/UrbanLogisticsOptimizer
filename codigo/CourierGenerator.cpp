#include "CourierGenerator.h"
#include <fstream>
#include <unordered_set>
using namespace std;

vector<unsigned int> CourierGenerator::amountCouriers = {10, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};

CourierGenerator::CourierGenerator(const std::string &sampleFile, unsigned int numCouriers) {
    amountCouriers_Sample = numCouriers;
    ifstream input(sampleFile);
    getline(input, header);
    string line;
    instances = vector<std::string>(amountCouriers_Sample);
    unsigned int idx = 0;
    while(getline(input, line)){
        line = line.substr(0, line.find_last_of(' '));
        instances[idx] = line;
        idx++;
    }
    input.close();
}


string CourierGenerator::randomPlateGenerator(){
    string plate;
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (48 + (rand() % ( 57 - 48 + 1 )));
    plate += (char) (48 + (rand() % ( 57 - 48 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    return plate;
}


void CourierGenerator::generate(){
    unordered_set<string> usedPlates;
    for (auto amount:amountCouriers){
        string fileName = "../input/generated/couriers/" + to_string(amount) + ".txt";
        ofstream output(fileName);
        output << header << endl;
        for (int i=0;i<amount;i++){
            string plate;
            do{
                plate = randomPlateGenerator();
            } while(!usedPlates.insert(plate).second);
            output << instances[rand() % amountCouriers_Sample] << " " << plate << endl;
        }
        output.close();
    }
}

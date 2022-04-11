#include "CourierGenerator.h"
#include <fstream>
#include <unordered_set>
using namespace std;

vector<unsigned int> CourierGenerator::amountCouriers = {8, 64, 1000, 16000, 32000, 64000, 128000, 256000};

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

/**
 * Creates a random license plate.
 * @return Returns random license plate.
 */
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

/**
 * Uses a sample file of Couriers and the randomPlateGenerator to generate specified amount of Couriers (specified by the vector amountCouriers) with license plates and save them into files (saved in ../input/generated/couriers/)
 */
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

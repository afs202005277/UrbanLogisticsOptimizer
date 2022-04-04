//
// Created by andre on 04/04/2022.
//

#include "NormalPackageGenerator.h"
#include <fstream>
#include <unordered_set>

using namespace std;

vector<unsigned int> NormalPackageGenerator::amountNormalPackages = {8, 64, 1000, 16000, 32000, 64000, 128000, 256000, 512000, 1000000, 2000000};

NormalPackageGenerator::NormalPackageGenerator(const std::string &sampleFile, , unsigned int numPackages) {
    amountNormalPackages_Sample = numPackages;
    ifstream input(sampleFile);
    getline(input, header);
    string line;
    instances = vector<std::string>(amountNormalPackages_Sample);
    unsigned int idx = 0;
    while(getline(input, line)){
        instances[idx] = line;
        idx++;
    }
    input.close();
}

string NormalPackageGenerator::randomPlateGenerator(){
    string plate;
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (48 + (rand() % ( 57 - 48 + 1 )));
    plate += (char) (48 + (rand() % ( 57 - 48 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    return plate;
}

void NormalPackageGenerator::generate(){
    for (auto amount:amountNormalPackages){
        string fileName = "../input/generated/" + to_string(amount) + ".txt";
        ofstream output(fileName);
        if (output.is_open())
            int x = 5;
        output << header << endl;
        for (int i=0;i<amount;i++){
            output << instances[rand() % amountNormalPackages_Sample] << endl;
        }
        output.close();
    }
}
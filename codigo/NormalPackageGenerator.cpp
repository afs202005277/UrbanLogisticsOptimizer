#include "NormalPackageGenerator.h"
#include <fstream>
#include <unordered_set>

using namespace std;

vector<unsigned int> NormalPackageGenerator::amountNormalPackages = {10, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};

NormalPackageGenerator::NormalPackageGenerator(const std::string &sampleFile, unsigned int numPackages) {
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


void NormalPackageGenerator::generate(){
    for (auto amount:amountNormalPackages){
        string fileName = "../input/generated/normalPackages/" + to_string(amount) + ".txt";
        ofstream output(fileName);
        output << header << endl;
        for (int i=0;i<amount;i++){
            output << instances[rand() % amountNormalPackages_Sample] << endl;
        }
        output.close();
    }
}
//
// Created by andre on 04/04/2022.
//

#ifndef PROJETO1_NORMALPACKAGEGENERATOR_H
#define PROJETO1_NORMALPACKAGEGENERATOR_H
#include <vector>
#include <string>

class NormalPackageGenerator {
private:
    unsigned int amountNormalPackages_Sample;
    std::vector<std::string> instances;
    std::string header;
    static std::vector<unsigned int> amountNormalPackages;
public:
    NormalPackageGenerator(const std::string &sampleFile, unsigned int numPackages);

    void generate();

    std::string randomPlateGenerator();
};


#endif //PROJETO1_NORMALPACKAGEGENERATOR_H

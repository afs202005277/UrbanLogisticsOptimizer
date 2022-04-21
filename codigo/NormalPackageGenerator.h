#ifndef PROJETO1_NORMALPACKAGEGENERATOR_H
#define PROJETO1_NORMALPACKAGEGENERATOR_H
#include <vector>
#include <string>

class NormalPackageGenerator {
private:
    unsigned int amountNormalPackages_Sample;
    std::vector<std::string> instances;
    std::string header;
public:
    NormalPackageGenerator(const std::string &sampleFile, unsigned int numPackages);

    static std::vector<unsigned int> amountNormalPackages;

    /**
    * Uses a sample file of Normal Packages to generate a specified amount of Packages (specified by the vector amountNormalPackages) and save them into files (saved in ../input/generated/normalPackages/)
    */
    void generate();
};


#endif //PROJETO1_NORMALPACKAGEGENERATOR_H

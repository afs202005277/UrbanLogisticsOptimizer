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

    void generate();
};


#endif //PROJETO1_NORMALPACKAGEGENERATOR_H

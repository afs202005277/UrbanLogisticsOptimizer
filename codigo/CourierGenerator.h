#ifndef PROJETO1_COURIERGENERATOR_H
#define PROJETO1_COURIERGENERATOR_H

#include <vector>
#include <string>

class CourierGenerator {
private:
    unsigned int amountCouriers_Sample;
    std::vector<std::string> instances;
    std::string header;
    static std::vector<unsigned int> amountCouriers;

public:
    CourierGenerator(const std::string &sampleFile, unsigned int numCouriers);

    void generate();

    static std::string randomPlateGenerator();
};


#endif //PROJETO1_COURIERGENERATOR_H

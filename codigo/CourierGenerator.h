#ifndef PROJETO1_COURIERGENERATOR_H
#define PROJETO1_COURIERGENERATOR_H

#include <vector>
#include <string>

class CourierGenerator {
private:
    unsigned int amountCouriers_Sample;
    std::vector<std::string> instances;
    std::string header;
    /**
     * Creates a random license plate.
     * @return Returns random license plate.
     */
    static std::string randomPlateGenerator();
public:
    CourierGenerator(const std::string &sampleFile, unsigned int numCouriers);

    static std::vector<unsigned int> amountCouriers;

    /**
    * Uses a sample file of Couriers and the randomPlateGenerator to generate specified amount of Couriers (specified by the vector amountCouriers) with license plates and save them into files (saved in ../input/generated/couriers/)
    */
    void generate();
};


#endif //PROJETO1_COURIERGENERATOR_H

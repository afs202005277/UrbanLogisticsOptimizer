#ifndef PROJETO1_COURIER_H
#define PROJETO1_COURIER_H

#include <string>
#include <vector>
#include "TransportTypes.h"

class Courier {
private:
    std::string licensePlate;
    unsigned int volMax, volAtual=0;
    unsigned int pesoMax, pesoAtual=0;
    unsigned int transportFee;
    std::vector<NormalTransport> deliveries;
    double ratio;
    bool available;

public:
    Courier(std::string licensePlate, unsigned int volMax, unsigned int pesoMax, unsigned int transportFee);
    
    /**
    * A Courier is considered less than another if its maximum volume is less than the other courier and if equal, the maximum weight is used for the comparison.
    * @param rhs
    * @return True if considered less and false otherwise.
    */
    bool operator<(const Courier &rhs) const;
    
    /**
    * A Courier is considered more than another if its maximum volume is more than the other courier and if equal, the maximum weight is used for the comparison.
    * @param rhs
    * @return True if considered more and false otherwise.
    */
    bool operator>(const Courier &rhs) const;
    
    /**
    * Gets the courier's current deliveries amount.
    * @return Returns the current deliveries amount.
    */
    unsigned int getNumDeliveries() const;
    
    /**
    * Gets the courier's maximum volume.
    * @return Returns the maximum volume.
    */
    unsigned int getVolMax() const;
    
    /**
    * Gets the courier's current volume.
    * @return Returns the current volume.
    */
    unsigned int getVolAtual() const;
    
    /**
    * Gets the courier's maximum weight.
    * @return Returns the maximum weight.
    */
    unsigned int getPesoMax() const;
    
    /**
    * Gets the courier's current weight.
    * @return Returns the current weight.
    */
    unsigned int getPesoAtual() const;
    
    /**
     * Clears the deliveries vector.
     * Sets to 0 the variables pesoAtual e volAtual.
     */
    void eraseDeliveries();
    
    /**
    * Adds a package to the courier's deliveries list.
    * @param package the normal package to be added.
    */
    void addPackage(NormalTransport package);
    
    /**
    * Removes a normal package from the courier's deliveries list.
    * @param package the package to be removed.
    */
    void removePackage(NormalTransport package);
    
    /**
    * Gets the courier's ratio.
    * @return Returns the courier's ratio.
    */
    double getRatio() const;
    
    /**
    * Sets the courier's deliveries vector.
    * @param deliveries
    */
    void setDeliveries(const std::vector<NormalTransport> &deliveries);
    
    /**
    * Sets the courier's current volume.
    * @param volAtual
    */
    void setVolAtual(unsigned int volAtual);
    
    /**
    * Sets the courier's current weight.
    * @param pesoAtual
    */
    void setPesoAtual(unsigned int pesoAtual);
    
    /**
    * Gets the courier's transport fee.
    * @return Returns the transport fee.
    */
    unsigned int getTransportFee() const;
    
    /**
    * Checks if the courier is available for deliveries.
    * @return Returns true if available and false otherwise.
    */
    bool isAvailable() const;
    
    /**
    * Sets the courier's availability.
    * @param available
    */
    void setAvailable(bool available);
    
    /**
    * Gets the courier's license plate.
    * @return Returns the license plate.
    */
    const std::string &getLicensePlate() const;

    friend bool operator==(const Courier &lhs, const Courier &rhs);
};


#endif //PROJETO1_COURIER_H

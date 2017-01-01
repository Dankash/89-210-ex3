#ifndef ASS1_DRIVER_H
#define ASS1_DRIVER_H

#include <iostream>
#include "Cab.h"
#include "Passenger.h"

using namespace std;
/**
 * Create driver object.
 */
class Driver {
private:
    int id;
    int age;
    char maritalStatus;
    int yearsOfExperience;
    double averageSatisfaction;
    int cabId;
    Cab* cab;
    //friend class boost::serialization::access;


public:
    /*template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & maritalStatus;
        ar & yearsOfExperience;
        ar & averageSatisfaction;
        ar & cabId;
        ar & cab;
    }*/

    /**
 * Constructor.
 * @param id
 * @param age
 * @param materialStatus
 * @param yearsOfExperience
 * @param averageSatisfaction
 * @param cab
 * @return
 */
    Driver(int id, int age, char maritalChar, int yearsOfExperience, int cabId);

    /**
     *
     * @return empty driver.
     */
    Driver();

    /**
 * get driver's id.
 * @return id.
 */
    int getId() const;
    /**
 * set id.
 * @param id.
 */
    void setId(int id);
    /**
 * get driver's age.
 * @return age.
 */
    int getAge() const;
    /**
 * set age.
 * @param age.
 */
    void setAge(int age);
    /**
 * get marital status.
 * @return marital status.
 */
    char getMaritalStatus();
    /**
 * set marital status.
 * @param materialStatus.
 */
    void setMaritalStatus(char maritalStatus);
    /**
 * get YearsOfExperience.
 * @return gYearsOfExperience.
 */
    int getYearsOfExperience() const;
    /**
 * set YearsOfExperience.
 * @param yearsOfExperience.
 */
    void setYearsOfExperience(int yearsOfExperience);
    /**
 * get AverageSatisfaction
 * @return AverageSatisfaction.
 */
    double getAverageSatisfaction() const;
    /**
 * set AverageSatisfaction.
 * @param averageSatisfaction.
 */
    void setAverageSatisfaction(double averageSatisfaction);
    /**
 * get Cab.
 * @return cab.
 */
    Cab *getCab() const;
    /**
 * set cab.
 * @param cab.
 */
    void setCab(Cab *cab);
    /**
 * calculte fare.
 * @return CalculatedFare.
 */
    double CalculatedFare();

    /**
     *
     * @return cab id of the driver.
     */
    int getCabId() const;
/**
 *
 * @param cabId - set a cab id..
 */
    void setCabId(int cabId);

    friend ostream &operator<<(ostream &os, const Driver &driver);
    friend std::istream &operator>>(std::istream &input, Driver &driver);
};


#endif //ASS1_DRIVER_H

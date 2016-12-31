
#include "Driver.h"

Driver::Driver(int id, int age, char maritalChar, int yearsOfExperience,
               int cabId) : id(id), age(age), maritalStatus(maritalChar), yearsOfExperience(yearsOfExperience),
                           averageSatisfaction(0), cabId(cabId) {
}
Driver::Driver() {}

int Driver::getId() const {
    return id;
}

void Driver::setId(int id) {
    Driver::id = id;
}

int Driver::getAge() const {
    return age;
}

void Driver::setAge(int age) {
    Driver::age = age;
}

void Driver::setMaritalStatus(char maritalStatus) {
    Driver::maritalStatus = maritalStatus;
}

char Driver::getMaritalStatus() {
    return 0;
}

int Driver::getYearsOfExperience() const {
    return yearsOfExperience;
}

void Driver::setYearsOfExperience(int yearsOfExperience) {
    Driver::yearsOfExperience = yearsOfExperience;
}

double Driver::getAverageSatisfaction() const {
    return averageSatisfaction;
}

void Driver::setAverageSatisfaction(double averageSatisfaction) {
    Driver::averageSatisfaction = averageSatisfaction;
}

Cab *Driver::getCab() const {
    return cab;
}

void Driver::setCab(Cab *cab) {
    Driver::cab = cab;
}

int Driver::getCabId() const {
    return cabId;
}

void Driver::setCabId(int cabId) {
    Driver::cabId = cabId;
}

double CalculatedFare() {
    return 0.0;
}

ostream &operator<<(ostream &os, const Driver &driver) {
    char dummy;
    os << driver.id << dummy << driver.age << dummy << driver.maritalStatus
       << dummy << driver.yearsOfExperience << dummy << driver.averageSatisfaction
       << dummy << driver.cabId;
    return os;
}

std::istream &operator>>(std::istream &input, Driver &driver) {
    char dummy;
    input >> driver.id >> dummy >> driver.age >> dummy >> driver.maritalStatus
            >> dummy >> driver.yearsOfExperience >> dummy >> driver.averageSatisfaction
            >> dummy >> driver.cabId;
    return input;
}
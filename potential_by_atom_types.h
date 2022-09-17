#ifndef H_POTENTIAL_BY_ATOM_TYPES
#define H_POTENTIAL_BY_ATOM_TYPES

#include <string>
#include <vector>
class PotentialByAtomTypes {
    public:
    PotentialByAtomTypes();

    void addParametersByAtomTypes(int type1, int type2, double newSzeParam, double newEnergyParam);
    void updateParametersByAtomTypes(int type1, int type2, double newSizeParam, double newEnergyParam);

    std::string toString();

    virtual double calculateEnergy(int type1, int type2, double dSquared) = 0;

    protected:
    std::vector<std::vector<double> > sizeSquaredParams;
    std::vector<std::vector<double> > energyParams;
};

#endif

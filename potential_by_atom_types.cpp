#include <sstream>
#include "potential_by_atom_types.h"

PotentialByAtomTypes::PotentialByAtomTypes() : sizeSquaredParams(std::vector<std::vector<double> >()), energyParams(std::vector<std::vector<double> >()) {};

void PotentialByAtomTypes::addParametersByAtomTypes(int type1, int type2, double newSizeParam, double newEnergyParam) {
    // sizeSquaredParams and energyParams must always be a square symmetric matrix, such that
    // sizeSquaredParams[type1][type2] == sizeSquaredParams[type2][type1]
    //
    // Make them square, filling with 0.0's
    int newSize = std::max(type1,type2) + 1;
    for(int ii = 0; ii < sizeSquaredParams.size(); ii++){
        // Add new columns to existing rows
        if(sizeSquaredParams[ii].size() < newSize){
            sizeSquaredParams[ii].resize(newSize);
            energyParams[ii].resize(newSize);
        }
    }
    if(newSize > sizeSquaredParams.size()) {
        // Add new rows
        sizeSquaredParams.resize(newSize, std::vector<double>(newSize));
        energyParams.resize(newSize, std::vector<double>(newSize));
    }

    updateParametersByAtomTypes(type1,type2,newSizeParam,newEnergyParam);
};

void PotentialByAtomTypes::updateParametersByAtomTypes(int type1, int type2, double newSizeParam, double newEnergyParam) {
    if(std::max(type1,type2)>sizeSquaredParams.size()) throw;
    for(auto row : sizeSquaredParams){
        if(std::max(type1,type2) > row.size()) throw;
    }
    // Add the provided parameters
    sizeSquaredParams[type1][type2] = newSizeParam*newSizeParam;
    sizeSquaredParams[type2][type1] = newSizeParam*newSizeParam;
    energyParams[type1][type2] = newEnergyParam;
    energyParams[type2][type1] = newEnergyParam;
};

double PotentialByAtomTypes::getSizeParameter(int type1, int type2) {
    return sizeSquaredParams[type1][type2];
}
double PotentialByAtomTypes::getEnergyParameter(int type1, int type2) {
    return sizeSquaredParams[type1][type2];
}

std::string PotentialByAtomTypes::toString() {
    std::stringstream ss;
    ss.precision(5);
    for(int i = 0; i < sizeSquaredParams.size(); i++) {
        if(i>0)ss << std::endl;
        for(int j = 0; j < sizeSquaredParams[i].size(); j++) {
            ss << "  " << std::fixed << sizeSquaredParams[i][j] << "/" << energyParams[i][j];
        }
    }
    return ss.str();
};

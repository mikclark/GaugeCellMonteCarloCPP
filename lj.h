#include "potential_by_atom_types.h"
class LennardJones : public PotentialByAtomTypes {
    public:
    double calculateEnergy(int type1, int type2, double dSquared) {
        // e = 4 * e * ( (s/r)^12 - (s/r)^6 ) = 4 * e * (s/r)^6 * ( (s/r)^6 - 1 )
        if(dSquared==0.0)return 0.0;
        double sizeSquared = sizeSquaredParams[type1][type2];
        double ir2 = sizeSquared / dSquared;
        double ir6 = ir2 * ir2 * ir2;
        return 4.0 * energyParams[type1][type2] * ir6 * (ir6 - 1.0);
    } 
};

#include "potential_by_atom_types.h"
class LennardJones : public PotentialByAtomTypes {
    public:
    double calculateEnergy(int type1, int type2, double dSquared) {
        if(dSquared==0.0)return 0.0;
        if(type1<0||type2<0)return 0.0;

        // Energy = 4 * e * ( (s/r)^12 - (s/r)^6 ) = 4 * e * (s/r)^6 * ( (s/r)^6 - 1 )
        double sizeSquared = getSizeParameter(type1, type2);
        double ir2 = sizeSquared / dSquared;
        double ir6 = ir2 * ir2 * ir2;
        return 4.0 * getEnergyParameter(type1, type2) * ir6 * (ir6 - 1.0);
    } 
};

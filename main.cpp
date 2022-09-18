#include <iostream>
#include "state.h"
#include "lj.h"

int main() {
    double x = 1.122;
    State state;
    state.add(0, 0, 0, 0);
    state.add(x, 0, 0, 0);
    state.add(0, x, 0, 0);
    state.add(0, 0, x, 0);
    state.add(x, x, 0, 0);
    state.add(x, 0, x, 0);
    state.add(0, x, x, 0);
    state.add(x, x, x, 0);

    LennardJones lj;
    lj.addParametersByAtomTypes(0, 0, 1.0, 1.0);

    double energy = 0.0;
    int this_atom = 4;
    for(int i = 0; i < state.x.size(); i++) {
        if(i == this_atom)continue;
        double dx = state.x[i] - state.x[this_atom];
        double dy = state.y[i] - state.y[this_atom];
        double dz = state.z[i] - state.z[this_atom];
        double d2 = dx*dx + dy*dy + dz*dz;
        energy += lj.calculateEnergy(state.t[i], state.t[this_atom], d2);
    }
    std::cout << "Energy of atom " << this_atom << " = " << energy << std::endl;
    return 0;
}

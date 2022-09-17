#include "lj.h"
#include <iomanip>
#include <iostream>

int main(){
    LennardJones lj;
    std::cout << "Empty LennardJones:" << std::endl << lj.toString() << std::endl;

    lj.addParametersByAtomTypes(0, 0, 1.0, 1.0);
    std::cout << "One-species LennardJones:" << std::endl << lj.toString() << std::endl;

    lj.addParametersByAtomTypes(0, 1, 0.8, 1.2);
    lj.addParametersByAtomTypes(1, 1, 1.25, 2.0);
    std::cout << "Two-species LennardJones:" << std::endl << lj.toString() << std::endl;

    lj.updateParametersByAtomTypes(0, 1, 0.6, 1.6);
    std::cout << "Updated two-species LennardJones:" << std::endl << lj.toString() << std::endl;

    lj.addParametersByAtomTypes(3, 2, 1.25, 2.0);
    std::cout << "Sparse four-species LennardJones:" << std::endl << lj.toString() << std::endl;

    lj.addParametersByAtomTypes(2, 0, 0.2, 0.1);
    lj.addParametersByAtomTypes(3, 0, 0.3, 0.1);
    lj.updateParametersByAtomTypes(2, 2, 0.99, 1.0);
    lj.updateParametersByAtomTypes(3, 3, 1.0, 2.0);
    std::cout << "Updated four-species LennardJones:" << std::endl << lj.toString() << std::endl;

    std::cout << "Example energies for 1.0/1.0:" << std::endl;
    double e0, e1, e2, e3;
    for(double d = 0.9; d < 1.25; d+=0.01){
        e0 = lj.calculateEnergy(0, 0, d*d);
        e1 = lj.calculateEnergy(1, 1, d*d);
        e2 = lj.calculateEnergy(2, 2, d*d);
        e3 = lj.calculateEnergy(3, 3, d*d);
        std::cout << "  " << std::fixed << std::setprecision(5) << d << "  :  "
            << e0 << " , " << e1 << " , " << e2 << " , " << e3 << std::endl;
    }
}

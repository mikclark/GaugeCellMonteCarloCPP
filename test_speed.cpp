#include "state.h"
#include "lj.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

double run_with_iterators(State & state, LennardJones & lj) {
    double energy = 0.0;
    std::vector<double>::iterator x0, y0, z0, x1, y1, z1;
    std::vector<int>::iterator t0, t1;
    double dx, dy, dz, d2;
    for( x0 = state.x.begin(), y0 = state.y.begin(), z0 = state.z.begin(), t0 = state.t.begin();
                x0 < state.x.end(); x0++, y0++, z0++, t0++) {
        for( x1 = state.x.begin(), y1 = state.y.begin(), z1 = state.z.begin(), t1 = state.t.begin();
                    x1 < state.x.end(); x1++, y1++, z1++, t1++) {
            if(x0==x1)continue;
            dx = (*x0 - *x1);
            dy = (*y0 - *y1);
            dz = (*z0 - *z1);
            dx -= round(dx/state.boxLength)*state.boxLength;
            dy -= round(dy/state.boxLength)*state.boxLength;
            dz -= round(dz/state.boxLength)*state.boxLength;
            d2 = dx*dx + dy*dy + dz*dz;
            energy += lj.calculateEnergy(*t0, *t1, d2);
        }
    }
    return energy;
}

double run_with_indicies(State & state, LennardJones & lj) {
    double energy = 0.0;
    int i, j;
    double dx, dy, dz, d2;
    for( i = 0; i < state.x.size(); i++) {
        for( j = 0; j < state.x.size(); j++) {
            if(i==j)continue;
            dx = (state.x[i] - state.x[j]);
            dy = (state.y[i] - state.y[j]);
            dz = (state.z[i] - state.z[j]);
            dx -= round(dx/state.boxLength)*state.boxLength;
            dy -= round(dy/state.boxLength)*state.boxLength;
            dz -= round(dz/state.boxLength)*state.boxLength;
            d2 = dx*dx + dy*dy + dz*dz;
            energy += lj.calculateEnergy(state.t[i], state.t[j], d2);
        }
    }
    return energy;
}
double run_with_indicies2(State & state, LennardJones & lj) {
    double energy = 0.0;
    int i, j;
    double dx, dy, dz, d2;
    for( i = 0; i < state.x.size(); i++) {
        for( j = 0; j < state.x.size(); j++) {
            if(i==j)continue;
            dx = (state.x[i] - state.x[j]) - round((state.x[i] - state.x[j])/state.boxLength)*state.boxLength;
            dy = (state.y[i] - state.y[j]) - round((state.y[i] - state.y[j])/state.boxLength)*state.boxLength;
            dz = (state.z[i] - state.z[j]) - round((state.z[i] - state.z[j])/state.boxLength)*state.boxLength;
            d2 = dx*dx + dy*dy + dz*dz;
            energy += lj.calculateEnergy(state.t[i], state.t[j], d2);
        }
    }
    return energy;
}

static inline double square(double x){ return x*x;}
static inline double pbc(double d, double L){ return d - round(d/L)*L;}
double run_with_stl_bind(State & state, LennardJones & lj) {
    double energy = 0.0;
    int i, j;
    int n = state.x.size();
    std::vector<double> dx(n, 0.0), dy(n, 0.0), dz(n, 0.0), d2(n, 0.0), sigma(n, 0.0), epsilon(n, 0.0), ir2(n, 0.0), ir6(n, 0.0), ir12(n, 0.0);
    for( i = 0; i < n; i++) {
        std::transform(state.x.begin(), state.x.end(), dx.begin(),
                std::bind2nd(std::minus<double>(), state.x[i])
                );
        std::transform(state.y.begin(), state.y.end(), dy.begin(),
                std::bind2nd(std::minus<double>(), state.y[i])
                );
        std::transform(state.z.begin(), state.z.end(), dz.begin(),
                std::bind2nd(std::minus<double>(), state.z[i])
                );
        std::transform(dx.begin(), dx.end(), dx.begin(), std::bind(pbc, std::placeholders::_1, state.boxLength));
        std::transform(dy.begin(), dy.end(), dy.begin(), std::bind(pbc, std::placeholders::_1, state.boxLength));
        std::transform(dz.begin(), dz.end(), dz.begin(), std::bind(pbc, std::placeholders::_1, state.boxLength));
        
        // Set d2 to dx*dx
        std::transform(dx.begin(), dx.end(), d2.begin(), square);
        std::transform(dy.begin(), dy.end(), dy.begin(), square);
        std::transform(dz.begin(), dz.end(), dz.begin(), square);

        std::transform(dy.begin(), dy.end(), d2.begin(), d2.begin(), std::plus<double>());
        std::transform(dz.begin(), dz.end(), d2.begin(), d2.begin(), std::plus<double>());

        int this_type = state.t[i];
        std::transform(d2.begin(), d2.end(), state.t.begin(), ir12.begin(), [&lj, this_type](double dd, int tt){
                return lj.calculateEnergy(tt, this_type, dd);
                });
        energy += std::accumulate(ir12.begin(), ir12.end(), 0.0);

        /*
        std::transform(state.t.begin(), state.t.end(), sigma.begin(),
                std::bind( std::bind(&LennardJones::getSizeParameter,lj), state.t[i], std::placeholders::_2) );
        std::transform(state.t.begin(), state.t.end(), epsilon.begin(),
                std::bind( std::bind(&LennardJones::getEnergyParameter,lj), state.t[i], std::placeholders::_2) );

        std::transform(sigma.begin(), sigma.end(), d2.begin(), ir2.begin(), std::divides<double>() );
        std::transform(ir2.begin(), ir2.end(), ir6.begin(), square);
        std::transform(ir2.begin(), ir2.end(), ir6.begin(), ir6.begin(), std::multiplies<double>() );
        std::transform(ir6.begin(), ir6.end(), ir12.begin(), square);
        std::transform(ir12.begin(), ir12.end(), ir12.begin(), ir6.begin(), std::minus<double>() );
        std::transform(epsilon.begin(), epsilon.end(), ir12.begin(), ir12.begin(), std::multiplies<double>() );
        energy += 4.0*std::accumulate(ir12.begin(), ir12.end(), 0.0);
        */
    }
    return energy;
}

int main() {
    int n_atoms = 3000;
    double L = 100.0;

    double e, t;
    clock_t start, end;

    start = clock();
    LennardJones lj;
    lj.addParametersByAtomTypes(0, 0, 1.0, 1.0);
    lj.addParametersByAtomTypes(1, 0, 1.0, 1.0);
    lj.addParametersByAtomTypes(1, 1, 1.0, 1.0);
    lj.addParametersByAtomTypes(2, 0, 1.0, 1.0);
    lj.addParametersByAtomTypes(2, 1, 1.0, 1.0);
    lj.addParametersByAtomTypes(2, 2, 1.0, 1.0);
    State state(L);
    state.fillRandom({n_atoms/3, n_atoms/3, n_atoms/3});
    end = clock();
    std::cout << "Initialization took " << double(end - start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    start = clock();
    e = run_with_stl_bind(state, lj);
    end = clock();
    std::cout << "run_with_stl_bind energy = " << e << ", took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    start = clock();
    e = run_with_iterators(state, lj);
    end = clock();
    std::cout << "run_with_iterators energy = " << e << ", took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    start = clock();
    e = run_with_indicies(state, lj);
    end = clock();
    std::cout << "run_with_indicies energy = " << e << ", took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    start = clock();
    e = run_with_indicies2(state, lj);
    end = clock();
    std::cout << "run_with_indicies2 energy = " << e << ", took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;
    
    //run_with_stl(state, lj);
}

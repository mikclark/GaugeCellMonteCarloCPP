#include "state.h"
#include <string>
#include <sstream>

State::State(double boxLength) : boxLength(boxLength), x(), y(), z(), t(), n_atoms(0) {};
State::State(const State & state) : boxLength(state.boxLength), x(state.x), y(state.y), z(state.y), t(state.t), n_atoms(state.n_atoms) {};
State::State(double boxLength,
             const std::vector<double> & xx,
             const std::vector<double> & yy,
             const std::vector<double> & zz,
             const std::vector<int> & tt
) : boxLength(boxLength), x(), y(), z(), t()
{
    int input_n_atoms = xx.size();
    if(yy.size() != input_n_atoms || zz.size() != input_n_atoms || tt.size() != input_n_atoms){
        throw std::runtime_error("All input vectors to State() must be the same size");
    }
    double halfLength = 0.5*boxLength;
    for(int i = 0; i < input_n_atoms; i++) {
        if( (abs(xx[i]) <= halfLength) && (abs(yy[i]) <= halfLength) && (abs(zz[i]) <= halfLength) ) {
            x.push_back(xx[i]);
            y.push_back(yy[i]);
            z.push_back(zz[i]);
            t.push_back(tt[i]);
        }
    }
    n_atoms = x.size();
};

void State::add(double newx, double newy, double newz, int newt) {
    x.push_back(newx);
    y.push_back(newy);
    z.push_back(newz);
    t.push_back(newt);
    n_atoms++;
};

void State::remove(int i) {
    if( (i < 0) || (i >= x.size()) ){
        throw std::runtime_error("Cannot remove item as it does not exist in State's lists");
    }
    x.erase(x.begin() + i);
    y.erase(y.begin() + i);
    z.erase(z.begin() + i);
    t.erase(t.begin() + i);
    n_atoms--;
};

std::string State::toString() {
    std::stringstream ss;
    ss << "Box Length = " << boxLength << ", # atoms = " << n_atoms << std::endl;
    for(int i = 0; i < x.size(); i++) {
        ss << x[i] << " " << y[i] << " " << z[i] << " (" << t[i] << ")\n";
    }
    return ss.str();
};

void State::fillRandom(std::initializer_list<int> countOfEachType) {
    std::mt19937_64 rng(time(nullptr));
    this->fillRandom(rng, countOfEachType);
}
void State::fillRandom(std::mt19937_64 & rng, std::initializer_list<int> countOfEachType) {
    const double convert_to_length = boxLength/rng.max();
    int this_type = -1;
    for(auto nOfThisType : countOfEachType) {
        this_type++;
        for(int i = 0; i < nOfThisType; i++){
            this->add( (rng() - 0.5) * convert_to_length,
                      (rng() - 0.5) * convert_to_length,
                      (rng() - 0.5) * convert_to_length,
                      this_type );
        }
    }
    n_atoms = x.size();
}

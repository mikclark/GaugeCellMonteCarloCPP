#include "state.h"
#include <string>
#include <sstream>

State::State() : x(), y(), z(), t() {};
State::State(const State & state) : x(state.x), y(state.y), z(state.y), t(state.t) {};
State::State(const std::vector<double> & xx, const std::vector<double> & yy, const std::vector<double> & zz, const std::vector<int> & tt) : x(xx), y(yy), z(zz), t(tt) {};

void State::add(double newx, double newy, double newz, int newt) {
    x.push_back(newx);
    y.push_back(newy);
    z.push_back(newz);
    t.push_back(newt);
};

void State::remove(int i) {
    if( (i < 0) || (i >= x.size()) ){
        throw std::runtime_error("Cannot remove item as it does not exist in State's lists");
    }
    x.erase(x.begin() + i);
    y.erase(y.begin() + i);
    z.erase(z.begin() + i);
    t.erase(t.begin() + i);
};

std::string State::toString() {
    std::stringstream ss;
    for(int i = 0; i < x.size(); i++) {
        ss << x[i] << " " << y[i] << " " << z[i] << " (" << t[i] << ")\n";
    }
    return ss.str();
};

void State::fillRandom(double L, std::initializer_list<int> nn) {
    std::mt19937_64 rng(time(nullptr));
    this->fillRandom(rng, L, nn);
}
void State::fillRandom(std::mt19937_64 & rng, double L, std::initializer_list<int> nn) {
    const double convert_to_length = L/rng.max();
    int i_type = -1;
    for(auto ni : nn) {
        i_type++;
        for(int i = 0; i < ni; i++){
            this->add( rng() * convert_to_length,
                      rng() * convert_to_length,
                      rng() * convert_to_length,
                      i_type );
        }
    }
}

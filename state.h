#ifndef H_STATE
#define H_STATE

#include <initializer_list>
#include <random>
#include <string>
#include <vector>

class State {
public:
    State(double boxLength);
    State(const State & state);
    State(double boxLength, const std::vector<double> & x, const std::vector<double> & y, const std::vector<double> & z, const std::vector<int> & t);

    void add(double x, double y, double z, int t);
    void remove(int i);
    std::string toString();
    void fillRandom(std::initializer_list<int> nn);
    void fillRandom(std::mt19937_64 & rng, std::initializer_list<int> nn);

    double boxLength;
    int n_atoms;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    std::vector<int> t;
};

#endif

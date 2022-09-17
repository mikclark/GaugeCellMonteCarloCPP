#ifndef H_STATE
#define H_STATE

#include <initializer_list>
#include <random>
#include <string>
#include <vector>

class State {
public:
    State();
    State(const State & state);
    State(const std::vector<double> & x, const std::vector<double> & y, const std::vector<double> & z, const std::vector<int> & t);

    void add(double x, double y, double z, int t);
    void remove(int i);
    std::string toString();
    void fillRandom(double L, std::initializer_list<int> nn);
    void fillRandom(std::mt19937_64 & rng, double L, std::initializer_list<int> nn);

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    std::vector<int> t;
};

#endif

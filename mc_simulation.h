#include <random>
#include <string>
#include <vector>
class MonteCarloSimulation {
    public:
        MonteCarloSimulation(PotentialByAtomTypes & pot, State & state);
        MonteCarloSimulation(PotentialByAtomTypes & pot, State & state, std:mt19937_64 & rng);
        MonteCarloSimulation(PotentialByAtomTypes & pot, double boxLength);
        MonteCarloSimulation(PotentialByAtomTypes & pot, double boxLength, std:mt19937_64 & rng);

        doIterations(int n);
        setMoveDistance(double d);

        registerMetric(std::string metricName, Metric & metric);
        deleteMetric(std::string metricName);

        bool save_results = false;
    private:
        doOneIteration();

        moveMoleculeTrialStep();
        addMoleculeTrialStep();
        removeMoleculeTrialStep();

        State m_state;
        PotentialByAtomTypes m_potentials;
        std::mt19937_64 m_rng;
        double m_moveDistance;
        std::map<std::string, Metric> m_metrics;
}

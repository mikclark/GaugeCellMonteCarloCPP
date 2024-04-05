MonteCarloSimulation::MonteCarloSimulation(PotentialByAtomTypes & pot, double boxLength)
    : m_potential(pot), m_state(boxLength), m_rng(std::mt19937_64(time(nullptr))) {};

MonteCarloSimulation::MonteCarloSimulation(PotentialByAtomTypes & pot, State & state, std:mt19937_64 & rng)
    : m_potential(pot), m_state(state), m_rng(rng) {};

MonteCarloSimulation::MonteCarloSimulation(PotentialByAtomTypes & pot, State & state);
    : m_potential(pot), m_state(state), m_rng(std::mt19937_64(time(nullptr))) {};

MonteCarloSimulation::MonteCarloSimulation(PotentialByAtomTypes & pot, double boxLength, std:mt19937_64 & rng);
    : m_potential(pot), m_state(boxLength), m_rng(rng) {};


MonteCarloSimulation::setMoveDistance(double d) {
    m_moveDistance = d;
}



MonteCarloSimulation::moveMoleculeTrialStep() {
    int whichMolecule = m_rng() * m_state.nAtoms();

    // This is not spherically symmetric, but it's fast
    double newx = m_state[x] + m_moveDistance * (2.0*m_rng() - 1.0);
    double newx = m_state[x] + m_moveDistance * (2.0*m_rng() - 1.0);
    double newx = m_state[x] + m_moveDistance * (2.0*m_rng() - 1.0);

    double energy = 0.0;
    for(int i = 0; i <= m_state.nAtoms; i++) {
        double dx = (newx - m_state.x[i]);
        dx = dx - std::round(dx / m_state.boxLength) * m_state.boxLength;
        double rr = dx*dx;
        double dy = (newy - m_state.y[i]);
        rr += dy*dy;
        double dz = (newz - m_state.z[i]);
        rr += dz*dz;
        energy += m_potential.calculateEnergy(m_state.t[i], newt, rr)
    }

    double probability = 1.0;
    if(energy <= 0.0) {

    }
    if(probability >= 1.0 || probably >= m_rng()) {
        m_state.add(newx, newy, newz, newt);
    }
}

MonteCarloSimulation::addMoleculeTrialStep() {
    double newx = (m_rng() - 0.5) * m_state.boxLength;
    double newy = (m_rng() - 0.5) * m_state.boxLength;
    double newz = (m_rng() - 0.5) * m_state.boxLength;
    int newt = m_rng() * m_potential.countMoleculeTypes();

    double energy = 0.0;
    for(int i = 0; i <= m_state.nAtoms; i++) {
        double dx = (newx - m_state.x[i]);
        double rr = dx*dx;
        double dy = (newy - m_state.y[i]);
        rr += dy*dy;
        double dz = (newz - m_state.z[i]);
        rr += dz*dz;
        energy += m_potential.calculateEnergy(m_state.t[i], newt, rr)
    }

    double probability = 1.0;
    if(energy <= 0.0) {

    }
    if(probability >= 1.0 || probably >= m_rng()) {
        m_state.add(newx, newy, newz, newt);
    }
}

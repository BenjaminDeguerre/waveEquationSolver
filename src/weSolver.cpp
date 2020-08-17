#include "weSolver.hpp"

#include <math.h>

#include <iostream>

#include "function.hpp"

WESolver::WESolver() {
  this->deltaT = 0.01;
  this->deltaX = 0.01;
  this->u = 1;
}

WESolver::WESolver(double deltaX, double deltaT, double u)
    : deltaX(deltaX), deltaT(deltaT), u(u) {}

void WESolver::setDeltaX(double deltaX) { this->deltaX = deltaX; }

void WESolver::setDeltaT(double deltaT) { this->deltaT = deltaT; }

void WESolver::setU(double u) { this->u = u; }

double WESolver::getDeltaX() { return this->deltaX; }

double WESolver::getDeltaT() { return this->deltaT; }

double WESolver::getU() { return this->u; }

std::vector<double> WESolver::resolveOneStep(std::vector<double> initial,
                                             int method) {
  switch (method) {
    case 1:
      return oneStepUpwindExplicit(initial);
      break;
    case 2:
      return oneStepUpwindImplicit(initial);
      break;
    case 3:
      return oneStepLaxWendroff(initial);
      break;
    case 4:
      return oneStepRichtmyer(initial);
      break;
    default:
      return oneStepUpwindImplicit(initial);
      break;
  }
}

std::vector<double> WESolver::resolve(std::vector<double> initial, double t,
                                      int method) {
  switch (method) {
    case 1:
      return resolveUpwindExplicit(initial, t);
      break;
    case 2:
      return resolveUpwindImplicit(initial, t);
      break;
    case 3:
      return resolveLaxWendroff(initial, t);
      break;
    case 4:
      return resolveRichtmyer(initial, t);
      break;
    default:
      return resolveUpwindImplicit(initial, t);
      break;
  }
}

std::vector<double> WESolver::oneStepUpwindExplicit(
    std::vector<double> initial) {
  for (int s = initial.size() - 1; s > 0; s--) {
    initial[s] = initial[s] - this->u * (this->deltaT / this->deltaX) *
                                  (initial[s] - initial[s - 1]);
  };

  return initial;
}

std::vector<double> WESolver::oneStepUpwindImplicit(
    std::vector<double> initial) {
  for (int s = 1; s < initial.size() - 1; s++) {
    initial[s] =
        (initial[s] * this->deltaX + this->u * initial[s - 1] * this->deltaT) /
        (this->deltaX + this->u * this->deltaT);
  };
  return initial;
}

std::vector<double> WESolver::halfTimeFriedrichs(std::vector<double> initial) {
  std::vector<double> res(initial);
  for (int s = initial.size() - 2; s > 0; s--) {
    res[s] = (initial[s + 1] + initial[s - 1]) / 2 -
             this->deltaT * this->u / (4 * this->deltaX) *
                 (initial[s + 1] - initial[s - 1]);
  };
  return res;
}

std::vector<double> WESolver::oneStepLaxWendroff(std::vector<double> initial) {
  std::vector<double> res(initial);
  for (int s = 1; s < initial.size() - 2; s++) {
    res[s] = (initial[s] -
              u * (deltaT * (initial[s + 1] - initial[s - 1]) / (2 * deltaX)) +
              ((deltaT * deltaT * u * u / (2 * deltaX * deltaX)) *
               (initial[s + 1] - 2 * initial[s] + initial[s - 1])));
  };
  return res;
}

std::vector<double> WESolver::oneStepRichtmyer(std::vector<double> initial) {
  std::vector<double> halfTime;
  for (int s = initial.size() - 2; s > 0; s--) {
    halfTime = halfTimeFriedrichs(initial);
    initial[s] = initial[s] - this->u * this->deltaT / (2 * this->deltaX) *
                                  (halfTime[s + 1] - halfTime[s - 1]);
  };
  return initial;
}

std::vector<double> WESolver::resolveUpwindExplicit(std::vector<double> initial,
                                                    double time) {
  for (int t = 0; t < time / this->deltaT; t++) {
    initial = oneStepUpwindExplicit(initial);
  }

  return initial;
}

std::vector<double> WESolver::resolveUpwindImplicit(std::vector<double> initial,
                                                    double time) {
  for (int t = 0; t < round(time / this->deltaT); t++) {
    initial = oneStepUpwindImplicit(initial);
  }
  return initial;
}

std::vector<double> WESolver::resolveLaxWendroff(std::vector<double> initial,
                                                 double time) {
  for (int t = 0; t < round(time / this->deltaT); t++) {
    initial = oneStepLaxWendroff(initial);
  }

  return initial;
}

std::vector<double> WESolver::resolveRichtmyer(std::vector<double> initial,
                                               double time) {
  for (int t = 0; t < round(time / this->deltaT); t++) {
    initial = oneStepRichtmyer(initial);
  }

  return initial;
}

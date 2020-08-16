#ifndef WE_SOLVER
#define WE_SOLVER

#include <vector>
/**
 * @file weSolver.hpp
 * @author Benjamin Deguerre
 * @version 0.1
 * @date 26 november 2016
 */

/**
 * @class WESolver
 *
 * Class that represent a solver for the advection equation. Allow the user to
 * specify the steps in time/space and the value of u.
 */
class WESolver {
 public:
  /**
   * Constructor for WESolver. Initialize deltaT to 0.01, deltaX to 0.01 and u
   *to 1.
   **/
  WESolver();

  /**
   * Second constructor of WESolver.
   * @param deltaX The value of the size of one step in space
   * @param deltaT The value of the size of one step in time
   * @param u The value of u in the equation
   * @throw NegativeValueException If one of the delta is negative.
   **/
  WESolver(double deltaX, double deltaT, double u);

  /**
   * Setter for deltaX.
   * @param deltaX
   * @throw NegativeValueException If the delta is negative.
   **/
  void setDeltaX(double deltaX);

  /**
   * Setter for deltaT.
   * @param deltaT
   * @throw NegativeValueException If the delta is negative.
   **/
  void setDeltaT(double deltaT);

  /**
   * Setter for U.
   * @param u
   **/
  void setU(double u);

  /**
   * Getter for deltaX.
   * @return double
   **/
  double getDeltaX();

  /**
   * Getter for deltaT.
   * @return double
   **/
  double getDeltaT();

  /**
   * Getter for u.
   * @return double
   **/
  double getU();

  /**
   * Solver for the equation
   * Allow to estimate the system one step further in time.
   * Four method are available
   *  <ul>
   *   <li>1, for Upwind explicit</li>
   *   <li>2, for Upwind implicit</li>
   *   <li>3, for Lax-Wendroff</li>
   *   <li>4, for Richtmyer</li>
   *   <li>default will use Upwind implicit</li>
   *  </ul>
   *
   * @param initial The std::vector<double> of the initials values of the
   *function to be estimated.
   * @param method The number of the method to be used.
   * @return std::vector<double> The estimated solution
   **/
  std::vector<double> resolveOneStep(std::vector<double> initial, int method);

  /**
   * Solver for the equation
   * Allow to estimate the system to a point in time.
   * Four method are available
   *  <ul>
   *   <li>1, for Upwind explicit</li>
   *   <li>2, for Upwind implicit</li>
   *   <li>3, for Lax-Wendroff</li>
   *   <li>4, for Richtmyer</li>
   *   <li>default will use Upwind implicit</li>
   *  </ul>
   *
   * @param initial The std::vector<double> of the initials values of the
   *function to be estimated.
   * @param t The point in time to estimate the function to (from 0 to t).
   * @param method The number of the method to be used.
   * @return std::vector<double> The estimated solution.
   * @throw NegativeValueException When t is negative.
   **/
  std::vector<double> resolve(std::vector<double> initial, double t,
                              int method);

 private:
  double deltaT;
  double deltaX;
  double u;

  std::vector<double> oneStepUpwindExplicit(std::vector<double> initial);
  std::vector<double> oneStepUpwindImplicit(std::vector<double> initial);
  std::vector<double> halfTimeRichtmyer(std::vector<double> initial);
  std::vector<double> halfTimeFriedrichs(std::vector<double> initial);
  std::vector<double> oneStepLaxWendroff(std::vector<double> initial);
  std::vector<double> oneStepRichtmyer(std::vector<double> initial);

  std::vector<double> resolveUpwindExplicit(std::vector<double> initial,
                                            double t);
  std::vector<double> resolveUpwindImplicit(std::vector<double> initial,
                                            double t);
  std::vector<double> resolveLaxWendroff(std::vector<double> initial, double t);
  std::vector<double> resolveRichtmyer(std::vector<double> initial, double t);
};
#endif

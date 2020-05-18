#include "spline.h"

#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "quadpp.h"

int main()
{
  const std::size_t npts = 1001;
  const double low = 0, high = 1;

  Eigen::ArrayXd xs, rs, ys, jac;
  quadpp::SemiInifiniteIntegralMesh(npts, low, high, xs, rs, jac);
  ys = jac * Eigen::exp(-rs);
  ys.tail(1) = 0;

  auto result1 =
      quadpp::spline::Integrate(xs, ys, quadpp::spline::SplineType::Steffen);
  auto result2 =
      quadpp::spline::Integrate(xs, ys, quadpp::spline::SplineType::Cubic);
  auto result3 =
      quadpp::spline::Integrate(xs, ys, quadpp::spline::SplineType::Akima);

  std::cout << "Integrating exp(-r) from 0 to ∞."
            << "\n";
  std::cout << "Using Steffen splines: " << std::setprecision(10) << std::fixed
            << result1 << "\n";
  std::cout << "Using Cubic splines: " << result2 << "\n";
  std::cout << "Using Akima splines: " << result3 << "\n";
}

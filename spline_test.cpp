#include <iostream>
#include <iomanip>
#include <cmath>
#include <Eigen/Dense>
#include "spline.h"

int main()
{
  const int num = 1001;

  Eigen::ArrayXd xs = Eigen::ArrayXd::LinSpaced(num, 0, 1);
  Eigen::ArrayXd ys = xs.unaryExpr([](double x) {
                           double r = x / (1 - x);
                           double dr = 1 / ((1 - x) * (1 - x));
                           return dr * std::exp(-r);
                         });
  ys.tail(1) = 0;

  auto result1 = quad::spline::Integrate(xs, ys);
  auto result2 = quad::spline::Integrate(xs, ys, "cubic");
  auto result3 = quad::spline::Integrate(xs, ys, "akima");

  std::cout << "Integrating exp(-r) from 0 to ∞." << "\n";
  std::cout << "Using Steffen splines: " << std::setprecision(10) << std::fixed << result1 << "\n";
  std::cout << "Using Cubic splines: " << result2 << "\n";
  std::cout << "Using Akima splines: " << result3 << "\n";
}

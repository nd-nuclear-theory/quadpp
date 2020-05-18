/*******************************************************************************
 quadpp.h

 Quadrature utility functions.

 Language: C++11
 Soham Pal
 Iowa State University
*******************************************************************************/

#ifndef QUADPP_H_
#define QUADPP_H_

#include <Eigen/Dense>

namespace quadpp {
// Integrals over the semi-infinite domain can be transformed to an integral
// over a finite domain by the following variable transformation:
// r = (x - a) / (b - x), where r is the original integration variable, x is
// the new integration variable and a, and b are the limits of the finite
// domain. This introduces a jacobian in the integral, (b - a) / (b - x)^2.
//
// Produces a linearly spaced mesh of points between a and b for
// semi-infinite integrals and the corresponding Jacobian. The last element of
// in the Jacobian array nan / inf, because unlike numpy, Eigen's
// implementation of a linearly spaced array does not have an option to
// exclude the end point. As such it falls to the user to ensure that the
// array passed to the integration routines in quadpp does not have any nan /
// inf values. One way would be to set the last element of the function values
// array to the limiting value of the function when r → ∞. If no such limit
// exists, then this is not a right way to do the integration in anyways.
void SemiInfiniteIntegralMesh(const std::size_t& npts, const double& a,
                              const double& b, Eigen::ArrayXd& x,
                              Eigen::ArrayXd& r, Eigen::ArrayXd& jac)
{
  x.setLinSpaced(static_cast<int>(npts), 0., 1.);
  r = (x - a) / (b - x);
  jac = (b - a) / Eigen::square(b - x);
}
}  // namespace quadpp

#endif

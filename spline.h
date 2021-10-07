/*******************************************************************************
 spline.h

 C++ wrapper for GSL's integration via spline interpolation routines.

 Language: C++11
 Soham Pal
 Iowa State University
*******************************************************************************/

// GSL provides implementations for Cubic, Akima, and Steffen splines.
// These routines can only compute one dimensional integration over a finite
// domain, [a, b]. Integrals over semi-infinite ([a, ∞), or (-∞, a]), or
// infinite ((-∞, ∞)) domains must first be converted to an integration over a
// finite domain by appropriate variable transformation.

#ifndef SPLINE_H_
#define SPLINE_H_

#include <Eigen/Dense>
#include <stdexcept>
#include <string>

namespace quadpp {
namespace spline {
// enum class for the three different types of splines in GSL.
enum class SplineType { Steffen, Akima, Cubic };

// Wrapper for GSL's spline integration function.
// Arguments:
//  xs (Eigen::ArrayXd&): Array of (linearly spaced) points from 0 to 1.
//  ys (Eigen::ArrayXd&): Array of function values at the points in xs.
//  st (SplineType&): Steffen / Akima / Cubic splines.
// Returns:
//  Value of the integral.
double Integrate(const Eigen::ArrayXd& xs, const Eigen::ArrayXd& ys,
                 const SplineType& st = SplineType::Steffen);
}  // namespace spline
}  // namespace quadpp

#endif

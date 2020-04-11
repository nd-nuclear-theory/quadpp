/*******************************************************************************
 spline.h

 C++ wrapper for GSL's integration via spline interpolation routines.

 Language: C++11
 Soham Pal
 Iowa State University
*******************************************************************************/

// GSL provides implementations for Cubic, Akima, and Steffen splines.
// These routines can only compute one dimensional integration over a finite
// domain, [a, b]. Integrals over semi-infinite ((a, ∞), or (-∞, a)), or
// infinite ((-∞, ∞)) domains must first be converted to an integration over a
// finite domain by appropriate variable transformation.

#ifndef SPLINE_H_
#define SPLINE_H_

#include <string>
#include <stdexcept>
#include <gsl/gsl_spline.h>

namespace quad {
  namespace spline {
    template <typename Array>
    double Integrate(const Array& xs,
                     const Array& ys,
                     const std::string& method="steffen") {
      if (xs.size() != ys.size()) {
        throw std::runtime_error("Arrays do not have same dimensions.");
      }

      if (method != "steffen" && method != "akima" && method != "cubic") {
        throw std::runtime_error("Undefined interpolation type.");
      }

      auto m = xs.size();

      gsl_interp_accel *acc = gsl_interp_accel_alloc();

      const gsl_interp_type *t = gsl_interp_steffen;
      if (method == "cubic") {
        t = gsl_interp_cspline;
      }
      if (method == "akima") {
        t = gsl_interp_akima;
      }

      gsl_spline *spline = gsl_spline_alloc(t, m);

      gsl_spline_init(spline, xs.data(), ys.data(), m);

      double integral = gsl_spline_eval_integ(spline, xs.data()[0], xs.data()[m-1], acc);

      gsl_spline_free(spline);
      gsl_interp_accel_free(acc);

      return integral;
    }
  }
}

#endif

#include "spline.h"

#include <gsl/gsl_spline.h>

namespace quadpp {
namespace spline {

double Integrate(const Eigen::ArrayXd& xs, const Eigen::ArrayXd& ys,
                 const SplineType& st)
{
  if (xs.size() != ys.size()) {
    throw std::runtime_error("Arrays do not have same dimensions.");
  }

  if (st != SplineType::Steffen && st != SplineType::Akima
      && st != SplineType::Cubic) {
    throw std::runtime_error("Undefined interpolation type.");
  }

  auto m = xs.size();

  gsl_interp_accel* acc = gsl_interp_accel_alloc();

  const gsl_interp_type* t = gsl_interp_steffen;
  if (st == SplineType::Cubic) {
    t = gsl_interp_cspline;
  }
  if (st == SplineType::Akima) {
    t = gsl_interp_akima;
  }

  gsl_spline* spline = gsl_spline_alloc(t, m);

  gsl_spline_init(spline, xs.data(), ys.data(), m);

  double integral =
      gsl_spline_eval_integ(spline, xs.data()[0], xs.data()[m - 1], acc);

  gsl_spline_free(spline);
  gsl_interp_accel_free(acc);

  return integral;
}
}  // namespace spline
}  // namespace quadpp

// PointsOdeInitState.cpp

#include "PointsOdeInitState.h"
#include "ode_num_int/util/m_const.h"

namespace ctm {
namespace points {

CTM_FACTORY_REGISTER_TYPE( PointsOdeInitState, "points" )

double PointsOdeInitState::initialTime() const
{
    return 0;
}

auto PointsOdeInitState::initialState() const -> V
{
    auto _2n = 2*m_pointCount;
    V result(2*m_pointCount);
    double h = 2*M_PI / m_pointCount;
    double t = 0;
    auto rnd = []() {
        return static_cast<double>(rand())/RAND_MAX;
    };
    for (unsigned int _2i=0; _2i<_2n; _2i+=2, t+=h) {
        auto angle = t + m_param_amp * sin(t*m_param_periods);
        auto r = 1 + m_wave_amp*sin(t*m_wave_periods);
        auto x = r*cos(angle*m_x_periods);
        auto y = r*sin(angle*m_y_periods);
        if (m_xy_random_amp > 0) {
            x += m_xy_random_amp*rnd();
            y += m_xy_random_amp*rnd();
        }
        result[_2i] = x;
        result[_2i+1] = y;
    }
    return result;
}

auto PointsOdeInitState::parameters() const -> Parameters
{
    Parameters result;
    result["point_count"] = m_pointCount;
    result["x_periods"] = m_x_periods;
    result["y_periods"] = m_y_periods;
    result["param_periods"] = m_param_periods;
    result["wave_periods"] = m_wave_periods;
    result["wave_amp"] = m_wave_amp;
    result["param_amp"] = m_param_amp;
    result["xy_random_amp"] = m_xy_random_amp;
    return result;
}

void PointsOdeInitState::setParameters(const Parameters& parameters)
{
    using namespace std;
    using namespace placeholders;
    OptionalParameters::maybeLoadParameter(parameters, "point_count", m_pointCount);
    OptionalParameters::maybeLoadParameter(parameters, "x_periods", m_x_periods);
    OptionalParameters::maybeLoadParameter(parameters, "y_periods", m_y_periods);
    OptionalParameters::maybeLoadParameter(parameters, "param_periods", m_param_periods);
    OptionalParameters::maybeLoadParameter(parameters, "wave_periods", m_wave_periods);
    OptionalParameters::maybeLoadParameter(parameters, "wave_amp", m_wave_amp);
    OptionalParameters::maybeLoadParameter(parameters, "param_amp", m_param_amp);
    OptionalParameters::maybeLoadParameter(parameters, "xy_random_amp", m_xy_random_amp);
}

} // namespace points
} // namespace ctm

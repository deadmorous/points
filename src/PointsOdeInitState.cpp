// PointsOdeInitState.cpp

#include "PointsOdeInitState.h"
#include "ode_num_int/util/m_const.h"

namespace points {

CTM_FACTORY_REGISTER_TYPE( PointsOdeInitState, "points" )

double PointsOdeInitState::initialTime() const
{
    return 0;
}

auto PointsOdeInitState::initialState() const -> V
{
    auto _2n = 2*m_size;
    V result(2*m_size);
    double h = 2*M_PI / m_size;
    double t = 0;
    for (unsigned int _2i=0; _2i<_2n; _2i+=2, t+=h) {
        result[_2i] = cos(t);
        result[_2i+1] = sin(t);
    }
    return result;
}

auto PointsOdeInitState::parameters() const -> Parameters
{
    Parameters result;
    result["size"] = m_size;
    return result;
}

void PointsOdeInitState::setParameters(const Parameters& parameters)
{
    using namespace std;
    using namespace placeholders;
    OptionalParameters::maybeLoadParameter(parameters, "size", m_size);
}

} // namespace points

// PointsOdeInitState.h

#ifndef _POINTSODEINITSTATE_H_
#define _POINTSODEINITSTATE_H_

#include "ode_num_int/OdeInitState.h"

namespace points {
using namespace ctm::math;

using VD = ctm::math::VectorData<double>;

class PointsOdeInitState :
    public OdeInitState<VD>,
    public ctm::FactoryMixin< PointsOdeInitState, OdeInitState<VD> >
{
public:
    typedef ctm::math::Vector< double > V;
    typedef OptionalParameters::Parameters Parameters;

    double initialTime() const override;
    V initialState() const override;

    Parameters parameters() const override;
    void setParameters(const Parameters& parameters) override;

private:
    unsigned int m_size = 10;
    unsigned int m_x_periods = 1;
    unsigned int m_y_periods = 1;
    unsigned int m_param_periods = 10;
    unsigned int m_wave_periods = 3;
    double m_wave_amp = 0;
    double m_param_amp = 0;
    double m_xy_random_amp = 0;
};

} // namespace points

#endif // _POINTSODEINITSTATE_H_

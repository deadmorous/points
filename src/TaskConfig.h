// TaskConfig.h

#ifndef _TASKCONFIG_H_
#define _TASKCONFIG_H_

#include "points_ode.h"
#include "ode_num_int/OdeSolverConfiguration.h"

namespace points {

class TaskConfig
{
public:
    static OdeSolverConfiguration<VD>& cfg();

private:
    static bool m_initialized;
    static OdeSolverConfiguration<VD> m_cfg;
};

} // namespace points

#endif // _TASKCONFIG_H_

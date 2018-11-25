// TaskConfig.h

#ifndef _TASKCONFIG_H_
#define _TASKCONFIG_H_

#include "ode_num_int/OdeSolverConfiguration.h"
#include "vec_type.h"

namespace ctm {

class TaskConfig
{
public:
    static math::OdeSolverConfiguration<VD>& cfg();

private:
    static bool m_initialized;
    static math::OdeSolverConfiguration<VD> m_cfg;
};

} // namespace ctm

#endif // _TASKCONFIG_H_

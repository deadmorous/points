// TaskConfig.cpp

#include "TaskConfig.h"
namespace ctm {

bool TaskConfig::m_initialized = false;
math::OdeSolverConfiguration<VD> TaskConfig::m_cfg;

math::OdeSolverConfiguration<VD>& TaskConfig::cfg()
{
    if (!m_initialized) {
        m_initialized = true;
        m_cfg.setValue("rhs", "points");
        m_cfg.setValue("output_con", "con_solution");
        m_cfg.setValue("time", 10);
    }
    return m_cfg;
}

//    V x0( 2 );
//    x0[0] = 0.5;
//    auto sc = cfg.apply( set<unsigned int>(), 0, x0 );
//    solveOde( &cfg, &sc );

} // namespace ctm

#include "ode_num_int/OdeNumIntClassesRegistrator.h"
#include "vec_type.h"
// #include "ode_num_int/OdeTestModelClassesRegistrator.h"

void registerTypes()
{
    using namespace ctm;
    using namespace math;
    // using namespace testmodels;

    OdeNumIntClassesRegistrator<VD> registrator;
    // OdeTestModelClassesRegistrator<VD> modelRegistrator;
}

// ModelRoles.h

#ifndef _MODELROLES_H_
#define _MODELROLES_H_

#include <Qt>

namespace ctm {

struct ModelRoles
{
    enum {
        IsFactoryObject = Qt::UserRole,
        TypeRegistryGetter
    };
};

} // namespace ctm

#endif // _MODELROLES_H_

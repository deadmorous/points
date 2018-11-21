// points_ode.h

#ifndef _POINTS_ODE_H_
#define _POINTS_ODE_H_

#include "ode_num_int/OdeRhs.h"

namespace points {
using namespace ctm::math;

using VD = ctm::math::VectorData<double>;

class PointsOdeRhs :
    public OdeRhs< VD >,
    public ctm::FactoryMixin< PointsOdeRhs, OdeRhs<VD> >
    {
    public:
        typedef ctm::math::Vector< double > V;
        typedef V::value_type real_type;
        typedef OptionalParameters::Parameters Parameters;

        explicit PointsOdeRhs() :
            m_n( 10 )
            {}

        unsigned int secondOrderVarCount() const {
            return 0;
            }

        unsigned int firstOrderVarCount() const {
            return 2*m_n;
            }

        unsigned int zeroFuncCount() const {
            return 0;
            }

        void rhs( V& dst, real_type time, const V& x ) const
        {
            auto _2n = m_n << 1;
            dst.resize(_2n);
            dst.clear();
            for (int _2i=0; _2i<_2n; _2i+=2) {
                auto _2inext = (_2i+2)%_2n;
                auto dx = x[_2inext] - x[_2i];
                auto dy = x[_2inext+1] - x[_2i+1];
                auto idr = 1./sqrt(dx*dx+dy*dy);
                dx *= idr;
                dy *= idr;
                dst[_2i] += dx;
                dst[_2i+1] += dy;
                dst[_2inext] -= dx;
                dst[_2inext+1] -= dy;
            }
            this->odeRhsPostObservers( time, x, dst, this );
        }

        Parameters parameters() const
            {
            Parameters result;
            result["point_count"] = m_n;
            return result;
            }

        void setParameters( const Parameters & parameters )
            {
            this->maybeLoadParameter( parameters, "point_count", m_n );
            }

        Parameters helpOnParameters() const
            {
            Parameters result;
            result["point_count"] = "Number of points";
            return result;
            }

        std::string helpOnType() const {
            return "Points in plane (TODO: more help)";
            }

    private:
        int m_n;    // Point count
    };

} // namespace points

#endif // _POINTS_ODE_H_

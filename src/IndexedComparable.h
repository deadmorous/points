// IndexedComparable.h

#ifndef _INDEXEDCOMPARABLE_H_
#define _INDEXEDCOMPARABLE_H_

#include <map>
#include "ode_num_int/infra/cxx_assert.h"

namespace ctm {

template <class I, class T>
class IndexedComparable
{
public:
    IndexedComparable() : m_lastIndex()
    {
    }

    I insert(const T& x)
    {
        auto ix = m_x2i.find(x);
        if (ix == m_x2i.end()) {
            auto i = ++m_lastIndex;
            m_x2i[x] = i;
            m_i2x[i] = x;
            return i;
        }
        else
            return ix->second;
    }

    void remove(const T& x)
    {
        auto ix = m_x2i.find(x);
        ASSERT(ix != m_x2i.end());
        auto i = ix->second;
        auto ii = m_i2x.find(i);
        ASSERT(ii != m_i2x.end());
        m_x2i.erase(ix);
        m_i2x.erase(ii);
    }

    void removeIndex(const I& i)
    {
        auto ii = m_i2x.find(i);
        ASSERT(ii != m_i2x.end());
        auto x = ii->second;
        auto ix = m_x2i.find(x);
        ASSERT(ix != m_x2i.end());
        m_x2i.erase(ix);
        m_i2x.erase(ii);
    }

    void maybeRemove(const T& x)
    {
        auto ix = m_x2i.find(x);
        if (ix != m_x2i.end())
        {
            auto i = ix->second;
            auto ii = m_i2x.find(i);
            ASSERT(ii != m_i2x.end());
            m_x2i.erase(ix);
            m_i2x.erase(ii);
        }
    }

    void maybeRemoveIndex(const I& i)
    {
        auto ii = m_i2x.find(i);
        if (ii != m_i2x.end())
        {
            auto x = ii->second;
            auto ix = m_x2i.find(x);
            ASSERT(ix != m_x2i.end());
            m_x2i.erase(ix);
            m_i2x.erase(ii);
        }
    }

    const T& byIndex(const I& i) const
    {
        auto ii = m_i2x.find(i);
        ASSERT(ii != m_i2x.end());
        return ii->second;
    }

    const I& index(const T& x) const
    {
        auto ix = m_x2i.find(x);
        ASSERT(ix != m_x2i.end());
        return ix->second;
    }
    bool hasIndex(const I& i) const
    {
        return m_i2x.find(i) != m_i2x.end();
    }

    bool hasValue(const T& x) const
    {
        return m_x2i.find(x) != m_x2i.end();
    }

    void clear()
    {
        *this = IndexedComparable<I,T>();
    }

private:
    std::map<I,T> m_i2x;
    std::map<T,I> m_x2i;
    I m_lastIndex;
};

} // namespace ctm

#endif // _INDEXEDCOMPARABLE_H_

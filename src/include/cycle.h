/* {{{ LICENSE
 * cycle.h
 * This file is part of cDea
 *
 * Copyright (C) 2012 - KiNaudiz
 *
 * cDea is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * cDea is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with cDea. If not, see <http://www.gnu.org/licenses/>.
 * }}} */

#ifndef DEA_CYCLE_H
#define DEA_CYCLE_H

#include <memory>

namespace dea
{

template<typename T,T Min,T Max>
class StaticStdOverload
{
    public:
        virtual ~StaticStdOverload() noexcept = default;
    protected:
        static const T Overload(T& t)
        {
            while (t > Max)
                t -= (Max+1-Min);
            while (t < Min)
                t += (Max+1-Min);
            return t;
        };
};

template<typename T,T Min,T Max>
class StaticCountStdOverload
{
    std::shared_ptr<long int> counter_ = {nullptr};

    public:
        virtual ~StaticCountStdOverload() noexcept = default;
        setCounter(const std::shared_ptr<long int>& counter)
            { counter_ = counter; }

    protected:
        const T Overload(T& t)
        {
            while (t > Max)
            {
                t -= (Max+1-Min);
                if (counter_) ++(*counter_);
            }
            while (t < Min)
            {
                t += (Max+1-Min);
                if (counter_) --(*counter_);
            }
            return t;
        };
};

template<typename T,T Min,T Max>
class StaticCountMaxOverload
{
    std::shared_ptr<size_t> counter_ = {nullptr};

    public:
        virtual ~StaticCountMaxOverload() noexcept = default;
        setCounter(const std::shared_ptr<size_t>& counter)
            { counter_ = counter; }

    protected:
        const T Overload(T& t)
        {
            while (t > Max)
            {
                t -= (Max+1-Min);
                if (counter_) ++(*counter_);
            }
            return t;
        };
};

template<typename T,T Min,T Max,T Step,
    template <typename,T,T> class OnOverload=StaticStdOverload>
class StaticCycle final : public OnOverload <T,Min,Max>
{
    typedef OnOverload<T,Min,Max> Base;
    T value_;

    public:
        StaticCycle() = default;
        template<typename... Args>
        StaticCycle(Args... args);
        StaticCycle(const StaticCycle&);
        StaticCycle(StaticCycle&&);
        template <typename U>
        StaticCycle& operator=(U&&);
        StaticCycle& operator=(const StaticCycle&);
        StaticCycle& operator=(StaticCycle&&);
        ~StaticCycle() noexcept;

        const T operator()() const { return value_; }
        StaticCycle& operator++();
        StaticCycle& operator--();
        StaticCycle& operator++(int); //TODO
        StaticCycle& operator--(int); //TODO
        template <typename U>
        StaticCycle& operator+=(U rhs);
        template <typename U>
        StaticCycle& operator-=(U rhs);

        /**
         * Does NOT swap OnOverload members
         */
        inline friend void swap(StaticCycle& lhs,StaticCycle& rhs) noexcept
        {
            std::swap(lhs.value_,rhs.value_);
        }
};

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
template<typename... Args>
StaticCycle<T,Min,Max,Step,OnOverload>::StaticCycle (Args... args)
    : OnOverload<T,Min,Max>{},value_{args...}
{
    Base::Overload(value_);
}

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>::~StaticCycle() noexcept {}

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>::StaticCycle
    (const StaticCycle<T,Min,Max,Step,OnOverload>& other) 
    : value_{other.value_}
{ }

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>::StaticCycle
    (StaticCycle<T,Min,Max,Step,OnOverload>&& other) 
{
    swap(*this,other);
}

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
template <typename U>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator=(U&& rhs)
{
    value_ = std::forward<U>(rhs); Base::Overload(value_); return *this;
}

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator=
    (const StaticCycle<T,Min,Max,Step,OnOverload>& rhs)
{
    auto tmp = rhs;
    swap(*this,tmp);
    return *this;
}

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator=
    (StaticCycle<T,Min,Max,Step,OnOverload>&& rhs)
{
    swap(*this,rhs);
    return *this;
}

template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator++()
{
    value_++; Base::Overload(value_); return *this;
}
template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator--()
{
    value_--; Base::Overload(value_); return *this;
}
template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
template <typename U>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator+=(U rhs)
{
    value_+=rhs; Base::Overload(value_); return *this;
}
template<typename T,T Min,T Max,T Step,template<typename,T,T> class OnOverload>
template <typename U>
StaticCycle<T,Min,Max,Step,OnOverload>&
StaticCycle<T,Min,Max,Step,OnOverload>::operator-=(U rhs)
{
    value_-=rhs; Base::Overload(value_); return *this;
}



} // namespace: dea

#endif

/* {{{ LICENSE
 * hierarchy.h
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

#ifndef DEA_HIERARCHY_H
#define DEA_HIERARCHY_H

// {{{ Includes
#include "typelist.h"
#include "typemap.h"
#include "conversion.h"

#include <type_traits>
// }}} Includes

namespace dea
{

// {{{ class GenScatterHierarchy
/*! \class dea::GenScatterHierarchy
 * Generates a scatter hierarchy.
 *
 * \c dea::GenScatter::Hierarchy<TList,Unit>
 * 
 * \tparam TList dea::Typelist of classes to build the Hierarchy with
 * \tparam Unit A struct<class> that acts as a holder for the classes in
 * your hierarchy
 *
 * Example:
 * \code
 * template <class T>
 * struct Holder
 * {
 *      T value_;
 * };
 * 
 * typedef GenScatterHierarchy<
 *      typename dea::TL::MakeTypelist<int,std::string,Widget>::Result,
 *      Holder> WidgetInfo;
 * \endcode
 */
template <typename TList, template <class> class Unit>
class GenScatterHierarchy;
template <typename T1, typename T2, template <class> class Unit>
class GenScatterHierarchy<Typelist<T1,T2>,Unit>
    : public GenScatterHierarchy<T1,Unit>
    , public GenScatterHierarchy<T2,Unit>
{
    public:
        typedef Typelist<T1,T2> TList;
        typedef GenScatterHierarchy<T1,Unit> LeftBase;
        typedef GenScatterHierarchy<T2,Unit> RightBase;

        template <typename T>
        struct Rebind
        {
            typedef Unit<T> Result;
        };
};
template <typename AtomicType, template <class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType>
{
    typedef Unit<AtomicType> LeftBase;

    template <typename T>
    struct Rebind
    {
        typedef Unit<T> Result;
    };
};
template <template <class> class Unit>
class GenScatterHierarchy<NullType,Unit>
{};
// }}} class GenScatterHierarchy

// {{{ class TupleUnit
/*! \class dea::TupleUnit
 * Holder for tuple types
 *
 * \tparam T Type to hold
 */
template <typename T>
struct TupleUnit
{
    T value_;
    operator T&() { return value_; }
    operator const T&() const { return value_; }
};
// }}} class TupleUnit

// {{{ class Tuple
/*! \class dea::Tuple
 * A class for tuple usage.
 *
 * \tparam TList dea::Typelist of types that tuple should contain
 */
template <typename TList>
struct Tuple : public GenScatterHierarchy<TList, TupleUnit>
{};
// }}} class Tuple

// {{{ typedef Field
/** \relates dea::GenScatterHierarchy
 * Allows you to access a specific field of a dea::GenScatterHierarchy.
 *
 * Example:
 * \code
 * template <class T>
 * struct Holder
 * {
 *      T value_;
 * };
 * 
 * typedef GenScatterHierarchy<
 *      typename dea::TL::MakeTypelist<int,int,std::string,Widget>
 *          ::Result,Holder> WidgetInfo;
 *
 * WidgetInfo obj;
 * 
 * auto str = Field<std::string>(obj);
 * \endcode
 *
 * \param obj dea::GenScatterHierarchy whose elements you want to
 * access
 * \tparam T Type you want to access
 *
 * Another implementation of this function looks like this:
 * \c Field<T,int i>(T obj)
 * 
 * This is used to access multiple elements of a hierarchy that share the same
 * type.
 *
 * Example:
 * \code
 * int i = Field<0>(obj);
 * int j = Field<1>(obj);
 * \endcode
 */
template <typename T, typename H>
typename H::template Rebind<T>::Result& Field(H& obj)
{ return obj; }
template <typename T, typename H>
const typename H::template Rebind<T>::Result& Field(const H& obj)
{ return obj; }
template <typename H, unsigned int i> struct FieldHelper;
template <typename H>
struct FieldHelper<H,0>
{
    typedef typename H::TList::Head ElementType;
    typedef typename H::template Rebind<ElementType>::Result UnitType;

    enum
    {
        isTuple = Conversion<UnitType,TupleUnit<ElementType>>::sameType,
        isConst = std::is_const<H>::value
    };

    typedef const typename H::LeftBase ConstLeftBase;
    typedef typename Select<isConst, ConstLeftBase,
        typename H::LeftBase>::Result LeftBase;
    typedef typename Select<isTuple, ElementType,
        UnitType>::Result UnqualifiedResultType;
    typedef typename Select<isConst, const UnqualifiedResultType,
        UnqualifiedResultType>::Result ResultType;
    
    static ResultType& Do(H& obj)
    {
        LeftBase leftBase = obj;
        return leftBase;
    }
};
template <class H, unsigned int i>
struct FieldHelper
{
    typedef typename TL::TypeAt<typename H::Tlist, i>::Result ElementType;
    typedef typename H::template Rebind<ElementType>::Result UnitType;

    enum
    {
        isTuple = Conversion<UnitType, TupleUnit<ElementType>>::sameType,
        isConst = std::is_const<H>::value
    };

    typedef const typename H::RightBase ConstRightBase;
    typedef typename Select<isConst, ConstRightBase,
        typename H::RightBase>::Result RightBase;
    typedef typename Select<isTuple, ElementType,
        UnitType>::Result UnqualifiedResultType;
    typedef typename Select<isConst, const UnqualifiedResultType,
        UnqualifiedResultType>::Result ResultType;

    static ResultType& Do(H& obj)
    {
        RightBase& rightBase = obj;
        return FieldHelper<RightBase,i-1>::Do(rightBase);
    };
};
template <int i, class H>
typename FieldHelper<H,i>::ResultType&
Field(H& obj)
{
    return FieldHelper<H,i>::Do(obj);
}
// }}} typedef Field

// {{{ class GenLinearHiearchy
// TODO: documentation for GenLinearHiearchy
template 
<
    typename TList,
    template <typename AtomicType,typename Base> class Unit,
    typename Root = NullType
>
class GenLinearHiearchy;
template
<
    typename T1, typename T2,
    template <class,class> class Unit,
    typename Root
>
class GenLinearHiearchy<Typelist<T1,T2>,Unit,Root>
    : public Unit<T1,GenLinearHiearchy<T2,Unit,Root>>
{};
template
<
    typename T,
    template <class,class> class Unit,
    typename Root
>
class GenLinearHiearchy<Typelist<T,NullType>,Unit,Root>
    : public Unit<T,Root>
{};
// }}} class GenLinearHiearchy

} // namespace: dea

#endif

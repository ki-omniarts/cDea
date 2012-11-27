/* {{{ LICENSE
 * typelist.h
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

#ifndef DEA_TYPELIST_H
#define DEA_TYPELIST_H

// {{{ Includes
#include "nullType.h"
// }}} Includes

namespace dea
{

// {{{ struct Typelist
/*!
 * Typelist, consisting of a Head and a Tail.
 * Typelists work recursive and end with a dea::NullType.
 *
 * To create a dea::Typelist, you should use dea::TL::MakeTypelist.
 *
 * \tparam T Head
 * \tparam U Tail
 */
template <typename T, typename U>
struct Typelist
{
    typedef T Head;
    typedef U Tail;
};
// }}} struct Typelist

// {{{ namespace: TL
namespace TL
{
    // {{{ struct MakeTypelist
    /*! \struct MakeTypelist
     * Creates a dea::Typelist according to its template arguments.
     *
     * Example:
     * \code
     * typedef typename dea::TL::MakeTypelist<int,float,double>::Result
     * Numbertypes;
     * \endcode
     */
    template<   typename    Head = NullType,
                typename... Tail>
    struct MakeTypelist
    {
        private:
            typedef typename MakeTypelist<Tail...>::Result TailResult;
        public:
            typedef Typelist<Head,TailResult> Result;
    };
    template<>
    struct MakeTypelist<>
    {
        typedef dea::NullType Result;
    };
    // }}} struct MakeTypelist

    // {{{ struct Length
    /*! \struct dea::TL::Length<TList>
     * Calculates the length of a dea::Typelist
     * which can be accessed by \c dea::TL::Length<TList>::value
     *
     * \tparam TList dea::Typelist whose elements you want to be counted
     */
    template<typename TList> struct Length;
    template<> struct Length<NullType>
    {
        enum { value = 0};
    };
    template <typename T, typename U>
    struct Length<Typelist<T,U>>
    {
        enum { value = 1 + Length<U>::value};
    };
    // }}} struct Length

    // {{{ struct TypeAt
    /*! \struct dea::TL::TypeAt
     * Let's you access a type on a given position of a dea::Typelist
     * by \c dea::TL::Length<TList,pos>::Result
     *
     * \tparam TList dea::Typelist holding the wanted element
     * \tparam pos Position of the wanted element
     */
    template <typename TList, unsigned int pos> struct TypeAt;
    template <typename Head, typename Tail>
    struct TypeAt<Typelist<Head,Tail>,0>
    {
        typedef Head Result;
    };
    template <typename Head, typename Tail, unsigned int pos>
    struct TypeAt<Typelist<Head,Tail>,pos>
    {
        typedef typename TypeAt<Tail, pos - 1>::Result Result;
    };
    // }}} struct TypeAt

    // {{{ struct IndexOf
    /*! \struct dea::TL::IndexOf
     * Returns the index of the first given type in a given
     * dea::Typelist or -1 if it is not found.
     * You can access the result by
     * dea::TL::IndexOf<TList,T>::value
     *
     * \tparam TList dea::Typelist to search through
     * \tparam T Type to search for
     */
    template <typename TList, typename T> struct IndexOf;
    template <typename T>
    struct IndexOf<NullType, T>
    {
        enum { value = -1 };
    };
    template <typename T, typename Tail>
    struct IndexOf<Typelist<T,Tail>,T>
    {
        enum { value = 0 };
    };
    template <typename Head, typename Tail, typename T>
    struct IndexOf<Typelist<Head,Tail>,T>
    {
        private:
            enum { temp = IndexOf<Tail,T>::value };
        public:
            enum { value = temp == -1 ? -1  : 1 + temp };
    };
    // }}} struct IndexOf

    // {{{ struct Append
    /** \struct dea::TL::Append
     * Appends a dea::Typelist or a type to a dea::Typelist.
     * You can access the new dea::Typelist by
     * \c dea::TL::Append<TList,T>::Result>.
     *
     * Example:
     * \code
     * typedef typename dea::TL::Append<
     *      typename dea::TL::MakeTypelist<int,float>,
     *      typename dea::TL::MakeTypelist<char,double>>::Result
     *      SignedTypes;
     * \endcode
     *
     * \tparam TList dea::Typelist to append to
     * \tparam T dea::Typelist or type that you want to append
     */
    template <typename TList, typename T> struct Append;
    template <>
    struct Append<NullType,NullType>
    {
        typedef NullType Result;
    };
    template <typename T>
    struct Append<NullType,T>
    {
        typedef MakeTypelist<T> Result;
    };
    template <typename Head, typename Tail>
    struct Append<NullType, Typelist<Head,Tail>>
    {
        typedef Typelist<Head,Tail> Result;
    };
    template <typename Head, typename Tail, typename T>
    struct Append<Typelist<Head,Tail>,T>
    {
        typedef Typelist<Head,
            typename Append<Tail, T>::Result> Result;
    };
    // }}} struct Append

    // {{{ struct Erase
    /*! \struct dea::TL::Erase
     * Erases the first found element of the given type from a
     * dea::Typelist.
     * The resulting dea::Typelist can be accessed by
     * \c dea::TL::Erase<TList,T>::Result
     * 
     * \tparam TList dea::Typelist in which there is the element
     * to erase
     * \tparam T Type to erase
     */
    template <typename TList, typename T> struct Erase;
    template <typename T>
    struct Erase<NullType,T>
    {
        typedef NullType Result;
    };
    template <typename T, typename Tail>
    struct Erase<Typelist<T,Tail>,T>
    {
        typedef Tail Result;
    };
    template <typename Head, typename Tail, typename T>
    struct Erase<Typelist<Head,Tail>,T>
    {
        typedef Typelist<Head, typename Erase<Tail,T>::Result> Result;
    };
    // }}} struct Erase

    // {{{ struct EraseAll
    /*! \struct dea::TL::EraseAll
     * Erases all elements of the given type from a dea::Typelist.
     *
     * You can access the new dea::Typelist by
     * \c dea::TL::EraseAll<TList,T>::Result
     *
     * \tparam TList dea::Typelist in which there are elements
     * that should be erased
     * \tparam T Type that should be erased from the dea::Typelist
     */
    template <typename TList, typename T> struct EraseAll;
    template <typename T>
    struct EraseAll<NullType,T>
    {
        typedef NullType Result;
    };
    template <typename T, typename Tail>
    struct EraseAll<Typelist<T,Tail>,T>
    {
        typedef typename EraseAll<Tail,T>::Result Result;
    };
    template <typename Head, typename Tail, typename T>
    struct EraseAll<Typelist<Head,Tail>,T>
    {
        typedef Typelist<Head, typename EraseAll<Tail,T>::Tesult> Result;
    };
    // }}} struct EraseAll

    // {{{ struct NoDuplicates
    /*! \struct dea::TL::NoDuplicates
     * Removes duplicates from a dea::Typelist.
     * The resulting dea::Typelist can be accesst by
     * \c dea::TL::NoDuplicates<TList>::Result
     *
     * \tparam TList dea::Typelist you want all duplicates to be all
     * duplicates erased in
     */
    template <typename TList> struct NoDuplicates;
    template <>
    struct NoDuplicates<NullType>
    {
        typedef NullType Result;
    };
    template <typename Head, typename Tail>
    struct NoDuplicates<Typelist<Head,Tail>>
    {
        private:
            typedef typename NoDuplicates<Tail>::Result L1;
            typedef typename Erase<L1, Head>::Result L2;
        public:
            typedef Typelist<Head,L2> Result;
    };
    // }}} struct NoDuplicates

    // {{{ struct Replace
    /*! \struct dea::TL::Replace
     * Replaces the first found type in a dea::Typelist you want to
     * replace.
     * The resulting dea::Typelist can be accessed by
     * \c dea::TL::Replace<TList,T,U>::Result
     *
     * \tparam TList dea::Typelist where a type should be replaced
     * by another one
     * \tparam T Type to replace
     * \tparam U Type to replace with
     */
    template <typename TList, typename T, typename U> struct Replace;
    template <typename T, typename U>
    struct Replace<NullType,T,U>
    {
        typedef NullType Result;
    };
    template <typename T, typename Tail, typename U>
    struct Replace<Typelist<T,Tail>,T,U>
    {
        typedef Typelist<U,Tail> Result;
    };
    template <typename Head, typename Tail, typename T, typename U>
    struct Replace<Typelist<Head,Tail>,T,U>
    {
        typedef Typelist<Head, typename Replace<Tail,T,U>::Tesult> Result;
    };
    // }}} struct Replace

    // {{{ struct ReplaceAll
    /*! \struct dea::TL::ReplaceAll 
     * Replaces all found elements of the given type you want to replace in a
     * dea::Typelist 
     * The resulting dea::Typelist can be accessed by
     * \c dea::TL::Replace<TList,T,U>::Result
     *
     * \tparam TList dea::Typelist where a type should be replaced
     * by another one
     * \tparam T Type to replace
     * \tparam U Type to replace with
     */
    template <typename TList, typename T, typename U> struct ReplaceAll;
    template <typename T, typename U>
    struct ReplaceAll<NullType,T,U>
    {
        typedef NullType Result;
    };
    template <typename T, typename Tail, typename U>
    struct ReplaceAll<Typelist<T,Tail>,T,U>
    {
        typedef Typelist<U, typename ReplaceAll<Tail,T,U>::Result> Result;
    };
    template <typename Head, typename Tail, typename T, typename U>
    struct ReplaceAll<Typelist<Head,Tail>,T,U>
    {
        typedef Typelist<Head, typename ReplaceAll<Tail,T,U>::Tesult> Result;
    };
    // }}} struct ReplaceAll

    // {{{ struct Reverse
    /*! \struct dea::TL::Reverse
     * Gives you a dea::Typelist in reverse order.
     * You can access the result by 
     * \c dea::TL::Reverse<TList>::Result.
     *
     * \tparam TList dea::Typelist to reverse
     */ 
    template <typename TList> struct Reverse;
    template <>
    struct Reverse<NullType>
    {
        typedef NullType Result;
    };
    template <typename Head, typename Tail>
    struct Reverse<Typelist<Head,Tail>>
    {
        typedef typename Append<typename Reverse<Tail>::Result,Head>::Result
            Result;
    };
    // }}} struct Reverse
}
// }}} namespace: TL

} // namespace: dea

#endif

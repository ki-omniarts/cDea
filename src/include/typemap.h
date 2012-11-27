/* {{{ TypeMap
 * typemap.h
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
 * along with cDea . If not, see <http://www.gnu.org/licenses/>.
 * }}} */

#ifndef DEA_TYPEMAP_H
#define DEA_TYPEMAP_H

namespace dea
{

// {{{ struct Int2Type
/*!
 * Lets you map an integer to a type.
 * \tparam v Integer to map
 */
template <int v>
struct Int2Type
{
    enum { value = v /*!< The integer value.*/ };
};
// }}} struct Int2Type

// {{{ struct Type2Type
/*!
 * Lets you map a type to a type.
 * \tparam T Original type
 */
template <typename T>
struct Type2Type
{
    /**
     * The original type.
     */
    typedef T OriginalType;
};
// }}} struct Type2Type

// {{{ struct Select
/*! \struct dea::Select
 * Decides between two given types.
 * You can access the chosen type by calling
 * \c dea::Select<flag,T,U>::Result
 * \tparam flag Boolean to choose between given types.
 * \tparam T Type to choose if \c flag equals \c true
 * \tparam U Type tp choose if \c flag equals \c false
 */
template <bool flag, typename T, typename U>
struct Select
{
    /**
     * Chosen type
     */
    typedef T Result;
};
template <typename T, typename U>
struct Select<false,T,U>
{
    typedef U Result;
};
// }}} struct Select

} // namespace: dea

#endif

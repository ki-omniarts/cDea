/* {{{ LICENSE
 * conversion.h
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

#ifndef DEA_CONVERSION_H
#define DEA_CONVERSION_H

namespace dea
{

// {{{ class Conversion
/*! \class dea::Conversion
 * Checks if two types are convertable to each other and if they are the same.
 *
 * You can check for convertion between two types by
 * \c dea::Conversion<T,U>::exists
 * and you can check if two are the same by
 * \c dea::Conversion<T,U>::sameType
 *
 * \tparam T First type
 * \tparam U Second type
 */
template <typename T, typename U>
class Conversion
{
    typedef char Small;
    class Big { char dummy[2]; };
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
    
    public:
        enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
        enum { sameType = false };
};
template <class T>
class Conversion<T,T>
{
    public:
        enum { exists = 1, sameType = 1 };
};
// }}} class Conversion

// {{{ DEA_SUPERSUBCLASS
/*! \relates dea::Conversion
 * Returns \c true if one class is derived from the other one.
 * \param T First class
 * \param U Second class
 */
#define DEA_SUPERSUBCLASS(T,U) \
    (dea::Conversion<const U*, const T*>::exists && \
    !dea::Conversion<const T*, const void*>::sameType)
// }}} DEA_SUPERSUBCLASS

} // namespace: dea
#endif

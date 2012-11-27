/* {{{ LICENSE
 * emptyType.h
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

#ifndef DEA_EMPTYTYPE_H
#define DEA_EMPTYTYPE_H

namespace dea
{

// {{{ class EmptyType
/*!
 * Just and empty type
 */
class EmptyType {};
// }}} EmptyType

// {{{ Comprehension
inline bool operator==(const EmptyType&, const EmptyType&)
{ return true; }

inline bool operator<=(const EmptyType&, const EmptyType&)
{ return true; }

inline bool operator>=(const EmptyType&, const EmptyType&)
{ return true; }

inline bool operator!=(const EmptyType&, const EmptyType&)
{ return false; }

inline bool operator>(const EmptyType&, const EmptyType&)
{ return false; }

inline bool operator<(const EmptyType&, const EmptyType&)
{ return false; }
// }}} Comprehension

} // namespace: dea

#endif

/* {{{ LICENSE
 * version.h.in
 * This file is part of cDea
 *
 * Copyright (C) 2012 - KiNaudiz
 *
 * cDea is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * cDea is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with cDea. If not, see <http://www.gnu.org/licenses/>.
 * }}} */


#ifndef DEA_VERSION_H
#define DEA_VERSION_H

/** @file version.h
 * Defines the version of the library.
 * 
 * Included by dea.h
 */

/** \namespace dea::version
 * Contains version informations of cDea
 */

namespace dea
{
namespace version
{

const unsigned int MAJOR = 1;
    ///< Major version of cDea.
const unsigned int MINOR = 0;
    ///< Minor version of cDea.
const unsigned int PATCH = 0;
    ///< Patch version of cDea.
const char NAME[]        = "";
    ///< Codename for the current cDea Version.

} // namespace: version
} // namespace: dea

#endif

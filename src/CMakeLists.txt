#
# CMakeLists.txt
# This file is part of cDea
#
# Copyright (C) 2012 - KiNaudiz
#
# cDea is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3.0 of the License, or (at your option) any later version.
#
# cDea is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with cDea. If not, see <http://www.gnu.org/licenses/>.
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# about the project
# -----------------
project( cDea )
SET( DEA_VERSION_MAJOR "1" )                                                  
SET( DEA_VERSION_MINOR "0" )                                                  
SET( DEA_VERSION_PATCH "0" )                                                  
SET( DEA_VERSION_NAME  "" )                                          
SET( DEA_VERSION_NAME  "\"${DEA_VERSION_NAME}\"" )                         
SET( DEA_VERSION
"${DEA_VERSION_MAJOR}.${DEA_VERSION_MINOR}.${DEA_VERSION_PATCH}" )
SET( LIB_NAME "Dea" )

# Paths
# -----
SET( DeaIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/include )

configure_file (                                                                 
    "${DeaIncludeDir}/version.h.in"
    "${DeaIncludeDir}/version.h"                          
)

# Install
# -------
install(DIRECTORY include/ DESTINATION include/Dea                            
      FILES_MATCHING PATTERN "*.h")
install(FILES "dea.h" DESTINATION include/)

# CPack
# -----

include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A small TMP library for C++11.")
set (CPACK_PACKAGE_VENDOR "KiNaudiz")
set (CPACK_RESOURCE_FILE_LICENSE                                                 
     "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${DEA_VERSION_MAJOR}")                      
set (CPACK_PACKAGE_VERSION_MINOR "${DEA_VERSION_MINOR}")                      
set (CPACK_PACKAGE_VERSION_PATCH "${DEA_VERSION_PATCH}")

# RPM:
#   cpack -D CPACK_RPM_PACKAGE_DEBUG=1 -D CPACK_RPM_SPEC_INSTALL_POST="/bin/true" -G RPM

set (CPACK_RPM_PACKAGE_LICENSE "LGPLv3+")
set (CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set (CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
set (CPACK_RPM_PACKAGE_REQUIRES "gcc >= 4.7")

include (CPack)

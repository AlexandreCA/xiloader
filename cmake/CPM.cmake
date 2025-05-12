# CPM.cmake
#
# Copyright (c) 2010-2014 Darkstar Dev Teams
# Copyright (c) 2023-2025 Fox_Mulder (adaptation Xbox 360)
#
# This file is part of xiloader, adapted for Xbox 360.
#
# CPM (CMake Package Manager) is disabled for Xbox 360, as external dependencies
# (e.g., argparse) are not required for this platform. All dependencies are either
# removed or integrated statically to ensure compatibility with the Xbox 360 SDK.
#
# If CPM is needed for additional dependencies, uncomment the following and ensure
# a local cache or manual download of CPM.cmake is provided to avoid network access.
#
# set(CPM_DOWNLOAD_VERSION 0.34.1)
#
# if(CPM_SOURCE_CACHE)
#   get_filename_component(CPM_SOURCE_CACHE ${CPM_SOURCE_CACHE} ABSOLUTE)
#   set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
# elseif(DEFINED ENV{CPM_SOURCE_CACHE})
#   set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
# else()
#   set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
# endif()
#
# if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
#   message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
#   file(DOWNLOAD
#        https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
#        ${CPM_DOWNLOAD_LOCATION}
#   )
# endif()
#
# include(${CPM_DOWNLOAD_LOCATION})

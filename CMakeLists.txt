#[[
===========================================================================

Copyright (c) 2010-2014 Darkstar Dev Teams
Copyright (c) 2023-2025 Fox_Mulder (adaptation Xbox 360)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

This file is part of DarkStar-server source code, adapted for Xbox 360.

===========================================================================
]]

cmake_minimum_required(VERSION 3.15)
project(xiloader CXX)

# Configure for Xbox 360 using the XDK
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ppc)
set(CMAKE_C_COMPILER "cl.exe") # XDK compiler
set(CMAKE_CXX_COMPILER "cl.exe")
set(CMAKE_LINKER "link.exe")

# Set C++ standard to C++11 for XDK compatibility
set_property(GLOBAL PROPERTY CXX_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY LINKER_LANGUAGE CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# XDK include and library paths (adjust to your XDK installation)
set(XDK_PATH "C:/Program Files/Microsoft Xbox 360 SDK")
set(CMAKE_INCLUDE_PATH "${XDK_PATH}/include")
set(CMAKE_LIBRARY_PATH "${XDK_PATH}/lib")

# xiloader executable
add_executable(xiloader
    src/console.cpp
    src/console.h
    src/defines.h
    src/ffxi.h
    src/ffximain.h
    src/functions.cpp
    src/functions.h
    src/helpers.h
    src/main.cpp
    src/network.cpp
    src/network.h
    src/polcore.h
)

# Include directories
target_include_directories(xiloader PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_INCLUDE_PATH}
)

# Link XDK libraries
target_link_libraries(xiloader PUBLIC
    xbox.lib
    xnet.lib
    xui.lib
    xinput.lib
)

# Output directory
message(STATUS "Setting output directory for xiloader to ${CMAKE_SOURCE_DIR}")
set_target_properties(xiloader PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}"
)

# Compiler and linker flags for Xbox 360
set(CMAKE_CXX_FLAGS "/EHsc /MT /W3 /bigobj")
set(CMAKE_EXE_LINKER_FLAGS "/MACHINE:XBOX360")

# Print configuration
message(STATUS "CMAKE_VERSION: ${CMAKE_VERSION}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")

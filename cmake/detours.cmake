# detours.cmake
#
# Copyright (c) 2010-2014 Darkstar Dev Teams
# Copyright (c) 2023-2025 Fox_Mulder (adaptation Xbox 360)
#
# This file is part of xiloader, adapted for Xbox 360.
#
# The Detours dependency is disabled for Xbox 360, as it relies on Win32 APIs and
# x86/x64 architecture, which are incompatible with the Xbox 360's PowerPC architecture
# and Xbox 360 SDK (XDK). If function interception is required (e.g., for FFXI or network),
# use XDK-compatible hooks or modify relevant interfaces (e.g., IGameMain, IFFXiEntry).
#
# If Detours is needed for a hybrid PC/Xbox 360 build, uncomment the following and
# include a local copy of Detours in third_party/detours, with modifications for PowerPC.
#
# CPMAddPackage(
#     NAME detours
#     GITHUB_REPOSITORY microsoft/Detours
#     GIT_TAG 66d6f2d34aba564d373083621cacf66ec51199b2
#     DOWNLOAD_ONLY YES
# )
# if (detours_ADDED)
#     file(COPY ${detours_SOURCE_DIR}/src/ DESTINATION ${detours_SOURCE_DIR}/detours/)
#     file(GLOB detours_sources ${detours_SOURCE_DIR}/detours/*.cpp)
#     list(REMOVE_ITEM detours_sources "${detours_SOURCE_DIR}/detours/uimports.cpp")
#     add_library(detours STATIC ${detours_sources})
#     target_compile_options(detours PRIVATE /W4 /WX /Zi /Gy /Gm- /Zl)
#     target_include_directories(detours
#       PUBLIC
#         $<BUILD_INTERFACE:${detours_SOURCE_DIR}>
#     )
# endif()

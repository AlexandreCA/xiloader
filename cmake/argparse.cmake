# argparse.cmake
#
# Copyright (c) 2010-2014 Darkstar Dev Teams
# Copyright (c) 2023-2025 Fox_Mulder (adaptation Xbox 360)
#
# This file is part of xiloader, adapted for Xbox 360.
#
# The argparse dependency is disabled for Xbox 360, as command-line argument
# parsing is not applicable. Parameters (e.g., server address, port) should be
# defined statically in src/defines.h or configured via an XUI interface.
#
# If argparse is required for a hybrid PC/Xbox 360 build, uncomment the following
# and include a local copy of argparse in third_party/argparse.
#
# CPMAddPackage(
#   NAME argparse
#   GITHUB_REPOSITORY p-ranav/argparse
#   GIT_TAG 557948f1236db9e27089959de837cc23de6c6bbd
# )

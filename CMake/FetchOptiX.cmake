# SPDX-FileCopyrightText: Copyright (c) 2022-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause
#

if (TARGET OptiX::OptiX)
  return()
endif()
 
include(FetchContent)
FetchContent_Declare(
    optix
    GIT_REPOSITORY https://github.com/NVIDIA/optix-dev.git
    GIT_TAG v8.0.0
    )
FetchContent_MakeAvailable(optix)

# Header-only library
add_library(OptiX INTERFACE IMPORTED)
set(OptiX_SOURCE_DIR "${optix_SOURCE_DIR}")
set(OptiX_INCLUDE_DIR "${optix_SOURCE_DIR}/include")
target_include_directories(OptiX INTERFACE "${OptiX_INCLUDE_DIR}")
add_library(OptiX::OptiX ALIAS OptiX)

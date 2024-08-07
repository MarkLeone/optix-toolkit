#
# Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Using the latest CMake is highly recommended, to ensure up-to-date CUDA language support.
cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
include(Policies)

project(ShaderUtil LANGUAGES C CXX CUDA)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

include(BuildConfig)

if(MSVC)
  add_definitions(-DNOMINMAX)
endif()

# Use fast math for CUDA code.
add_compile_options($<$<COMPILE_LANGUAGE:CUDA>:--use_fast_math>)

if(NOT TARGET CUDA::cuda_driver)
  find_package( CUDAToolkit 10.0 REQUIRED )
endif()

add_library(ShaderUtil INTERFACE)
add_library(OptiXToolkit::ShaderUtil ALIAS ShaderUtil)

target_sources(ShaderUtil
  PUBLIC 
  FILE_SET HEADERS 
  BASE_DIRS include
  FILES
  include/OptiXToolkit/ShaderUtil/AliasTable.h
  include/OptiXToolkit/ShaderUtil/CdfInversionTable.h
  include/OptiXToolkit/ShaderUtil/color.h
  include/OptiXToolkit/ShaderUtil/CudaSelfIntersectionAvoidance.h
  include/OptiXToolkit/ShaderUtil/DebugLocation.h
  include/OptiXToolkit/ShaderUtil/OptixSelfIntersectionAvoidance.h
  include/OptiXToolkit/ShaderUtil/PdfTable.h
  include/OptiXToolkit/ShaderUtil/Preprocessor.h
  include/OptiXToolkit/ShaderUtil/ray_cone.h
  include/OptiXToolkit/ShaderUtil/SelfIntersectionAvoidance.h
  include/OptiXToolkit/ShaderUtil/SelfIntersectionAvoidanceTypes.h
  include/OptiXToolkit/ShaderUtil/Transform4.h
  include/OptiXToolkit/ShaderUtil/Transform4Printer.h
  include/OptiXToolkit/ShaderUtil/vec_math.h
  include/OptiXToolkit/ShaderUtil/vec_printers.h
  )

target_include_directories(ShaderUtil INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
  )

set_target_properties(ShaderUtil PROPERTIES FOLDER "ShaderUtil")

if( BUILD_TESTING )
  add_subdirectory( tests )
endif()

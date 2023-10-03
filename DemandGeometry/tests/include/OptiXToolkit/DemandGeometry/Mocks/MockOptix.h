//
//  Copyright (c) 2022 NVIDIA Corporation.  All rights reserved.
//
//  NVIDIA Corporation and its licensors retain all intellectual property and proprietary
//  rights in and to this software, related documentation and any modifications thereto.
//  Any use, reproduction, disclosure or distribution of this software and related
//  documentation without an express license agreement from NVIDIA Corporation is strictly
//  prohibited.
//
//  TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
//  AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
//  INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//  PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
//  SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
//  LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
//  BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
//  INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
//  SUCH DAMAGES
//

#pragma once

#include <optix.h>
#include <optix_function_table.h>

#include <gmock/gmock.h>

extern "C" OptixFunctionTable g_optixFunctionTable;

namespace otk {
namespace testing {

class MockOptix
{
  public:
    MOCK_METHOD( OptixResult,
                 deviceContextCreate,
                 ( CUcontext fromContext, const OptixDeviceContextOptions* options, OptixDeviceContext* context ) );
    MOCK_METHOD( OptixResult, deviceContextDestroy, ( OptixDeviceContext context ) );
    MOCK_METHOD( OptixResult,
                 accelComputeMemoryUsage,
                 ( OptixDeviceContext            context,
                   const OptixAccelBuildOptions* accelOptions,
                   const OptixBuildInput*        buildInputs,
                   unsigned int                  numBuildInputs,
                   OptixAccelBufferSizes*        bufferSizes ) );
    MOCK_METHOD( OptixResult,
                 accelBuild,
                 ( OptixDeviceContext            context,
                   CUstream                      stream,
                   const OptixAccelBuildOptions* accelOptions,
                   const OptixBuildInput*        buildInputs,
                   unsigned int                  numBuildInputs,
                   CUdeviceptr                   tempBuffer,
                   size_t                        tempBufferSizeInBytes,
                   CUdeviceptr                   outputBuffer,
                   size_t                        outputBufferSizeInBytes,
                   OptixTraversableHandle*       outputHandle,
                   const OptixAccelEmitDesc*     emittedProperties,
                   unsigned int                  numEmittedProperties ) );
 #if OPTIX_VERSION < 70700
    MOCK_METHOD( OptixResult,
                 moduleCreateFromPTX,
                 ( OptixDeviceContext                 context,
                   const OptixModuleCompileOptions*   moduleCompileOptions,
                   const OptixPipelineCompileOptions* pipelineCompileOptions,
                   const char*                        PTX,
                   size_t                             PTXsize,
                   char*                              logString,
                   size_t*                            logStringSize,
                   OptixModule*                       module ) );
#else
    MOCK_METHOD( OptixResult,
                 moduleCreate,
                 ( OptixDeviceContext                 context,
                   const OptixModuleCompileOptions*   moduleCompileOptions,
                   const OptixPipelineCompileOptions* pipelineCompileOptions,
                   const char*                        PTX,
                   size_t                             PTXsize,
                   char*                              logString,
                   size_t*                            logStringSize,
                   OptixModule*                       module ) );
#endif
    MOCK_METHOD( OptixResult, moduleDestroy, ( OptixModule module ) );
    MOCK_METHOD( OptixResult,
                 builtinISModuleGet,
                 ( OptixDeviceContext                 context,
                   const OptixModuleCompileOptions*   moduleCompileOptions,
                   const OptixPipelineCompileOptions* pipelineCompileOptions,
                   const OptixBuiltinISOptions*       builtinISOptions,
                   OptixModule*                       builtinModule ) );
    MOCK_METHOD( OptixResult,
                 programGroupCreate,
                 ( OptixDeviceContext              context,
                   const OptixProgramGroupDesc*    programDescriptions,
                   unsigned int                    numProgramGroups,
                   const OptixProgramGroupOptions* options,
                   char*                           logString,
                   size_t*                         logStringSize,
                   OptixProgramGroup*              programGroups ) );
    MOCK_METHOD( OptixResult, programGroupDestroy, ( OptixProgramGroup group ) );
};

void initMockOptix( MockOptix& mock );

}  // namespace testing
}  // namespace otk

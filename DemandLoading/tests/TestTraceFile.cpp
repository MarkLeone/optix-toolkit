//
// Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "SourceDir.h"  // generated from SourceDir.h.in
#include <OptiXToolkit/Error/cudaErrorCheck.h>
#include "Util/TraceFile.h"

#include <OptiXToolkit/DemandLoading/DemandLoader.h>
#include <OptiXToolkit/DemandLoading/Options.h>
#include <OptiXToolkit/DemandLoading/TextureDescriptor.h>
#include <OptiXToolkit/ImageSource/EXRReader.h>

#include <cuda_runtime.h>

#include <gtest/gtest.h>

#include <thread>

using namespace demandLoading;
using namespace imageSource;

class TestTraceFile : public testing::Test
{
  public:
    void SetUp()
    {
        // Initialize CUDA.
        OTK_ERROR_CHECK( cudaSetDevice( 0 ) );
        OTK_ERROR_CHECK( cudaFree( nullptr ) );
    }

    unsigned int m_deviceIndex = 0;
    CUstream m_stream;
};

TEST_F( TestTraceFile, TestWriteAndRead )
{
    std::string textureFilename( getSourceDir() + "/Textures/TiledMipMapped.exr" );
    const char* traceFilename = "DemandLoadingTrace.dat";
    {
        TraceFileWriter writer( traceFilename );
        Options options;
        writer.recordOptions( options );

        std::shared_ptr<EXRReader> reader( new EXRReader( textureFilename.c_str() ) );
        TextureDescriptor          desc{};
        writer.recordTexture( reader, desc );

        // The first page represents the sampler for the first texture.
        unsigned int pageIds[1] = {0};
        writer.recordRequests( m_stream, pageIds, 1 );
    }
    replayTraceFile( traceFilename );
}

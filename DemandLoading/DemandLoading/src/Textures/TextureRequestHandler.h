//
// Copyright (c) 2021, NVIDIA CORPORATION. All rights reserved.
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

#pragma once

#include "RequestHandler.h"
#include <OptiXToolkit/Memory/MemoryBlockDesc.h>

#include <atomic>

namespace demandLoading {

class DemandLoaderImpl;
class DemandTextureImpl;

class TextureRequestHandler : public RequestHandler
{
  public:
    /// Default constructor.
    TextureRequestHandler() {}

    /// Construct TextureRequestHandler, which shares state with the DemandLoader.
    TextureRequestHandler( DemandTextureImpl* texture, DemandLoaderImpl* loader )
        : m_texture( texture )
        , m_loader( loader )
    {
    }

    /// Fill a request for the specified page using the given stream.  
    void fillRequest( CUstream stream, unsigned int pageId ) override;

    // Load or reload a page
    void loadPage( CUstream stream, unsigned int pageId, bool reloadIfResident );

    /// Get the associated texture.
    DemandTextureImpl* getTexture() const { return m_texture; }

    /// Unmap the backing storage associated with a texture tile or mip tail
    void unmapTileResource( CUstream stream, unsigned int pageId );

    /// Get the pageId for a tile
    unsigned int getTextureTilePageId( unsigned int mipLevel, unsigned int tileX, unsigned int tileY );

  private:
    DemandTextureImpl* m_texture = nullptr;
    DemandLoaderImpl*  m_loader = nullptr;

    void fillTileRequest( CUstream stream, unsigned int pageId, otk::TileBlockHandle bh );
    void fillMipTailRequest( CUstream stream, unsigned int pageId, otk::TileBlockHandle bh );
};

}  // namespace demandLoading

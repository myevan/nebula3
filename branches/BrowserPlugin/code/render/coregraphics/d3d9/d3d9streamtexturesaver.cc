//------------------------------------------------------------------------------
//  d3d9streamtexturesaver.cc
//  (C) 2007 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "coregraphics/d3d9/d3d9streamtexturesaver.h"
#include "coregraphics/d3d9/d3d9types.h"
#include "coregraphics/texture.h"

namespace Direct3D9
{
ImplementClass(Direct3D9::D3D9StreamTextureSaver, 'D9TS', Base::StreamTextureSaverBase);

using namespace IO;
using namespace CoreGraphics;

//------------------------------------------------------------------------------
/**
*/
bool
D3D9StreamTextureSaver::OnSave()
{
    n_assert(this->stream.isvalid());
    const Ptr<D3D9Texture>& tex = this->resource.downcast<D3D9Texture>();
    n_assert(tex->GetType() == Texture::Texture2D);
    IDirect3DTexture9* d3d9Texture = tex->GetD3D9Texture();
    n_assert(0 != d3d9Texture);

    DWORD maxLevels = d3d9Texture->GetLevelCount();
    SizeT mipLevelToSave = this->mipLevel;
    if (mipLevelToSave >= maxLevels)
    {
        mipLevelToSave = maxLevels - 1;
    }

    // get the mip surface from the texture
    IDirect3DSurface9* surf = NULL;
    HRESULT hr = d3d9Texture->GetSurfaceLevel(mipLevelToSave, &surf);
    n_assert(SUCCEEDED(hr));
    n_assert(NULL != surf);

    // convert file format to D3DX
    D3DXIMAGE_FILEFORMAT d3dxFmt = D3D9Types::AsD3DXImageFileFormat(this->format);

    // save through D3DX function
    ID3DXBuffer* d3dxBuffer = 0;
    hr = D3DXSaveSurfaceToFileInMemory(&d3dxBuffer,     // ppDestBuffer
                                       d3dxFmt,         // DestFormat
                                       surf,            // pSrcSurface
                                       NULL,            // pSrcPalette
                                       NULL);           // pSrcRect
    n_assert(SUCCEEDED(hr));
    n_assert(0 != d3dxBuffer);
    surf->Release();

    // write result to stream
    void* dataPtr  = d3dxBuffer->GetBufferPointer();
    DWORD dataSize = d3dxBuffer->GetBufferSize();
    this->stream->SetAccessMode(Stream::WriteAccess);
    if (this->stream->Open())
    {
        this->stream->Write(dataPtr, dataSize);
        this->stream->Close();
    }
    d3dxBuffer->Release();
    return true;
}

} // namespace Direct3D9

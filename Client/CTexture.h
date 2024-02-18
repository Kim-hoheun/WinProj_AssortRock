#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
    HDC      m_dc;
    HBITMAP  m_hBit;
    BITMAP   m_bitInfo;

public:
    // 텍스쳐를 파일로 부터 로딩한다
    void Load(const wstring& _strFilePath);

    // 파일로 부터 로딩하지 않고 직접만듬
    void Create(UINT _iWidth, UINT _iHeigth);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDc() { return m_dc ; }

private:
    CTexture();
    virtual ~CTexture();
    
    friend class CResMgr;

};

 
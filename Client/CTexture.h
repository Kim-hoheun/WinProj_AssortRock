#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
    HDC      m_dc;
    HBITMAP  m_hBit;
    BITMAP   m_bitInfo;

public:
    // �ؽ��ĸ� ���Ϸ� ���� �ε��Ѵ�
    void Load(const wstring& _strFilePath);

    // ���Ϸ� ���� �ε����� �ʰ� ��������
    void Create(UINT _iWidth, UINT _iHeigth);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDc() { return m_dc ; }

private:
    CTexture();
    virtual ~CTexture();
    
    friend class CResMgr;

};

 
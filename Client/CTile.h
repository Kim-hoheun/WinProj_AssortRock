#pragma once

#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{

private:
    CTexture*   m_pTileTex;
    int         m_iImgIdx;

public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;
    }

private:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void Save(FILE* _pTile);
    virtual void Load(FILE* _pTile);
    
    CLONE(CTile); // ��������ڸ� ȣ���ؼ� ��ü�� �������ִ� �Լ�

public:
    CTile();
    ~CTile();
};


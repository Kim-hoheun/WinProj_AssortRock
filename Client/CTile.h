#pragma once
#include "CObject.h"
class CTile :
    public CObject
{

private:

    virtual void render(HDC _dc);

public:
    CTile();
    ~CTile();
};


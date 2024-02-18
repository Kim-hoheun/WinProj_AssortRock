#pragma once
#include "CScene.h"
class CScene_Tool :
    public CScene
{

private:
    CUI* m_pUI;
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileIdx();

    void SaveTileData();                        // winAPI를 이용해서 파일 저장할 위치와 이름을 입력 받은 뒤 해당 절대경로를 
    void SaveTile(const wstring& _strFilePath); // SaveTile(const wstring& _strFilePath);에 입력해 준다
                                                // SaveTile은 타일의 개수와 각 타일마다의 개인정보(index)를 바이너리 파일에 저장한다
    void LoadTileData();

public:
    CScene_Tool();
    ~CScene_Tool();
};


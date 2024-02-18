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

    void SaveTileData();                        // winAPI�� �̿��ؼ� ���� ������ ��ġ�� �̸��� �Է� ���� �� �ش� �����θ� 
    void SaveTile(const wstring& _strFilePath); // SaveTile(const wstring& _strFilePath);�� �Է��� �ش�
                                                // SaveTile�� Ÿ���� ������ �� Ÿ�ϸ����� ��������(index)�� ���̳ʸ� ���Ͽ� �����Ѵ�
    void LoadTileData();

public:
    CScene_Tool();
    ~CScene_Tool();
};


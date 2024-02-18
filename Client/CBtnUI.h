#pragma once
#include "CUI.h"

#include "CScene.h" // ����Լ������͸� ����� ���� ���漱�����δ� �Ѿ ���� �ʴ´�
#include "CObject.h"// ����� �����ؼ� ���Ǹ� �˾ƾ� �Ѵ� �׷��� ���ε����� ������ ������ �ʴ´�
                    // �ּҰ� �Ѿ���� �ص� � Ŭ����Ÿ���� ������� �𸣱� ������ ���ε��� �ȵ�

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

// ����Լ�����Ʈ ����Ÿ�� (�ٸ� ��ü�� �ִ� ����� �Լ�������)
// ����Լ� �����ʹ� ȣ���� ��ü���� �ʿ��ϴ�
//typedef void(CScene_Tool::* TOOL_CSCENE_MEMFUNC)(void);
typedef void(CScene::*CSCENE_MEMFUNC)(void);
// ó�� �θ�Ÿ���̸� �ڽ�Ÿ�Ե� ���� �� ����
// �ڹ� ó�� �ֻ��� �θ� Object�� ������ ���� ObjectŸ������ ������
// ��� ����Լ��� ���� �� �־� Ȯ�强�� �����ϴ�
typedef void(CObject::* OBJECT_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
    
private:
    BTN_FUNC            m_pFunc;
    DWORD_PTR           m_param1;
    DWORD_PTR           m_param2;

    CSCENE_MEMFUNC      m_pSceneFunc; // ����Լ� �����͸� ����Ϸ��� ���漱�����δ� �ȵǰ� �ݵ�� ����� �����ؾ� �Ѵ� CScene����� �����ؾ���
    CScene*             m_pSceneInst; // ����Լ��� CSCENE_MEMFUNC�� ȣ���ϱ� ���� ��ü

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    void SetClickedCallBack(CScene* _Scene, CSCENE_MEMFUNC _pSceneFunc);
    

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};


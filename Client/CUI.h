#pragma once
#include "CObject.h"

// 추상클래스로 설계
class CUI :
    public CObject
{

private:
    vector<CUI*>  m_vecChildUI;
    CUI*          m_pParentUI;


    Vec2          m_vFinalPos;

    bool          m_bCamAffected; // UI 가 카메라에 영향을 받는 유무
    bool          m_bMouseOn;     // UI위에 마우스가 있는지 
    bool          m_bLbtnDown;    // UI에 왼쪽버튼이 눌린적이 있는지-> 매니저에서 값을 넣어줌

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    void AddChilde(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:

    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

private:
     void update_child();
     void finalupdate_child();
     void redner_child(HDC _dc);

     void MouseOnCheck();

public:

    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual CUI* Clone() = 0; // CUI는 추상 클래스로 설계를 해놨음
    //CLONE(CUI);
public:

    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};


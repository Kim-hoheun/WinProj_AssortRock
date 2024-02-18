#pragma once
#include "CUI.h"

#include "CScene.h" // 멤버함수포인터를 사용할 때는 전방선언으로는 넘어가 지지 않는다
#include "CObject.h"// 헤더를 참조해서 정의를 알아야 한다 그래야 바인딩에서 문제가 생기지 않는다
                    // 주소가 넘어오긴 해도 어떤 클래스타입의 멤버인지 모르기 때문에 바인딩이 안됨

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

// 멤버함수포인트 변수타입 (다른 객체에 있는 멤버의 함수포인터)
// 멤버함수 포인터는 호출할 객체까지 필요하다
//typedef void(CScene_Tool::* TOOL_CSCENE_MEMFUNC)(void);
typedef void(CScene::*CSCENE_MEMFUNC)(void);
// 처럼 부모타입이면 자식타입도 받을 수 있음
// 자바 처럼 최상위 부모 Object를 설정한 다음 Object타입으로 받으면
// 모든 멤버함수를 받을 수 있어 확장성이 용이하다
typedef void(CObject::* OBJECT_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
    
private:
    BTN_FUNC            m_pFunc;
    DWORD_PTR           m_param1;
    DWORD_PTR           m_param2;

    CSCENE_MEMFUNC      m_pSceneFunc; // 멤버함수 포인터를 사용하려면 전방선언으로는 안되고 반드시 헤더를 참조해야 한다 CScene헤더를 참조해야함
    CScene*             m_pSceneInst; // 멤버함수인 CSCENE_MEMFUNC을 호출하기 위한 객체

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


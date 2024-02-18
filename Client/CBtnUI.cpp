#include "CBtnUI.h"




CBtnUI::CBtnUI()
	:CUI(false)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneFunc(nullptr)
	, m_pSceneInst(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}


//void CBtnUI::update()
//{
//}

void CBtnUI::MouseOn()
{
	

}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	
	if (nullptr != m_pFunc) // 함수포인터가 초기화가 되었다면 함수포인터 m_pFunc을 실행
	{
		m_pFunc(m_param1, m_param2);
	}
	if (m_pSceneInst && m_pSceneFunc )
	{
		// 내가 호출할 객체의 원본을 호출 *m_pSceneInst
		// 원본에 접근해서 . 사용한 뒤 함수포인터를 이용해 원본에 접근 *m_pSceneFunc
		// 을 전체 가로쳐서 함수 호출()
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}

void CBtnUI::SetClickedCallBack(CScene* _Scene, CSCENE_MEMFUNC _pSceneFunc)
{

	m_pSceneInst = _Scene;
	m_pSceneFunc = _pSceneFunc;

}
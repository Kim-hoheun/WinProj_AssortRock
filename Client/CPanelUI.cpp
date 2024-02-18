#include "CPanelUI.h"

#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	:CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::update()
{

}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{    // IsLbtnDown은 CUI가 소유 중이고 Mgr에서 수정
	if (IsLbtnDown())//IsLbtnDown은 MouseLbtnDown이벤트 호출하고 true로 바뀐다
	{
		  Vec2 vDiff = MOUSE_POS - m_vDragStart;

		  
		  Vec2 vCurPos = GetPos();
		  vCurPos += vDiff;
		  SetPos(vCurPos);

		  m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}

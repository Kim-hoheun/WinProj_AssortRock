#include "pch.h"
#include "CKeyMgr.h"

#include "Core.h"
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'I',
	'U',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,

	VK_LBUTTON,
	VK_RBUTTON,

	//LAST,
};

CKeyMgr::CKeyMgr() {

}
CKeyMgr::~CKeyMgr() {

}
void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// HWND hMainWnd = Core::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();
	//��Ŀ�� ���ΰ�?
	if (nullptr != hWnd)
	{
		// ��Ŀ�� ��
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// Ű�� ���ȴ°�?
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				//yes
				// �������� ���ȴ°�?
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				// �������� ������ ����
				else {
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else {
				//no
				// �������� ���ȴ°�?
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else {
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;

			}
		} 
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(Core::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}
	//������ ��Ŀ�� ����
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}


	
}

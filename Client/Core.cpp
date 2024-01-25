#include "pch.h"
#include "Core.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"



Core::Core()
	:m_hwnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

Core::~Core()
{
	ReleaseDC(m_hwnd, m_hDC); // DCĿ�� ������Ʈ�� �ü���� �����ϹǷ� ������û�� �ؾ���

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int Core::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	
	//-------------------------------> �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0,0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true);
	// ȭ�� 100,100�� ���������� ������ ����, ���� ũ�� �־���
	SetWindowPos(m_hwnd, nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top, 0);
	//-------------------------------< �ػ󵵿� �°� ������ ũ�� ����
	
	// DC ����(�׸��׸��� ���ؼ�)
	m_hDC = GetDC(m_hwnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DF�� �����.
	// hdc�� �־��ִ� ������ �� hdc�� ��Ʈ�ʿ� �Ű� �׸��Ŷ� ȣȯ���� ���� �־��� (���ε��� ���󵵵�)
	// Ŀ�ο�����Ʈ�� ��Ʈ�� �ڵ��� �Ѱ���
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	
	// DC�� ó���� ���� �� 1�ȼ� ¥�� ��Ʈ���� ���缭 ���� �׷��� delete�ؼ� ��������
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init(); 
	CSceneMgr::GetInst()->init();

	

	// �ػ󵵿� �°� ������ ũ�� ����
	return S_OK;
}

void Core::progress()
{
	// Manager Updata
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	
	//============
	// Rendering
	//============
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	CSceneMgr::GetInst()->render(m_memDC);

	//���� CPU�� ó�� ����, �ݺ����̰� �ܼ��� �۾���, windowAPI�� CPU�� �̿��ؼ� ó�����ִ� �Լ��� ����
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();
}

void Core::update()
{
	/*Vec2 vPos = g_obj.GetPos();
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD) {
		vPos.x -= 200.f * CTimeMgr::GetInst( )->GetfDT();
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD) {
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
	}
	g_obj.SetPos(vPos); */
} 



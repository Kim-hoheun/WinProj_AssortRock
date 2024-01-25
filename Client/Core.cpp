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
	ReleaseDC(m_hwnd, m_hDC); // DC커널 오브젝트를 운영체제가 관리하므로 해제요청을 해야함

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int Core::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	
	//-------------------------------> 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0,0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true);
	// 화면 100,100을 시작점으로 조정된 가로, 세로 크기 넣어줌
	SetWindowPos(m_hwnd, nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top, 0);
	//-------------------------------< 해상도에 맞게 윈도우 크기 조정
	
	// DC 생성(그림그리기 위해서)
	m_hDC = GetDC(m_hwnd);

	// 이중 버퍼링 용도의 비트맵과 DF를 만든다.
	// hdc를 넣어주는 이유는 이 hdc의 비트맵에 옮겨 그릴거라서 호환성을 위해 넣어줌 (내부동작 몰라도됨)
	// 커널오브젝트인 비트맵 핸들을 넘겨줌
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	
	// DC를 처음에 만들 때 1픽셀 짜리 비트맵을 가춰서 나옴 그래서 delete해서 지워버림
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init(); 
	CSceneMgr::GetInst()->init();

	

	// 해상도에 맞게 윈도우 크기 조정
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

	//전부 CPU로 처리 중임, 반복적이고 단순한 작업을, windowAPI는 CPU를 이용해서 처리해주는 함수기 때문
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



#pragma once
#include "pch.h"
#include "Core.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

Core::Core()
	:m_hwnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

Core::~Core()
{
	ReleaseDC(m_hwnd, m_hDC); // DC커널 오브젝트를 운영체제가 관리하므로 해제요청을 해야함


	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);


	// 자주 사용 할 팬 및 브러쉬 생성
	CreateBrushPen();


	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init(); 
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();
	

	

	// 해상도에 맞게 윈도우 크기 조정
	return S_OK;
}

void Core::progress()
{	//================
	// Manager Updata
	//================

	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	//============
	// Scene Update -> update 다하고 finalUpdate도 진행
	//============

	CSceneMgr::GetInst()->update();

	// 충돌체크
	CCollisionMgr::GetInst()->update();
	
	// UI이벤트 체크
	CUIMgr::GetInst()->update();

	//============
	// Rendering
	//============
	// 화면 클리어 용 Rectangle
	Rectangle(m_pMemTex->GetDc(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	// back DC에 render를 함-------------------------------
	CSceneMgr::GetInst()->render(m_pMemTex->GetDc()); // 오브젝트들 랜더
	CCamera::GetInst()->render(m_pMemTex->GetDc()); // 카메라 효과 랜더
	// ---------------------------------------------------

	
	
	// main DC에 Back DC를 그려준다--------------------------------------------
	//전부 CPU로 처리 중임, 반복적이고 단순한 작업을, windowAPI는 CPU를 이용해서 처리해주는 함수기 때문
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDc(), 0, 0, SRCCOPY);
	// -----------------------------------------------------------------------

	//============
	// 타임 매니저 랜더 / window 상단에 프레임수 표시
	//============
	CTimeMgr::GetInst()->render();


	//================
	// 이벤트 지연처리
	//================
	CEventMgr::GetInst()->update();


}

void Core::CreateBrushPen()
{
	// 사실 이미 자체적으로 윈도우에서 만들어논걸 우리가 가져다 쓰는 것임
	// 윈도우에서 만들어 놓은 것으로 따로 우리가 삭제하지 않아도 됩니다.
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// red, blue, green pen / pen들은 이미 만들어져있지 않음 내가 아라서 해제해줘야함
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB( 0, 0, 255));
}




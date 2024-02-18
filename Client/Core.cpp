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
	ReleaseDC(m_hwnd, m_hDC); // DCĿ�� ������Ʈ�� �ü���� �����ϹǷ� ������û�� �ؾ���


	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// ���� ���۸� �뵵�� �ؽ��� ������ �����
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);


	// ���� ��� �� �� �� �귯�� ����
	CreateBrushPen();


	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init(); 
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();
	

	

	// �ػ󵵿� �°� ������ ũ�� ����
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
	// Scene Update -> update ���ϰ� finalUpdate�� ����
	//============

	CSceneMgr::GetInst()->update();

	// �浹üũ
	CCollisionMgr::GetInst()->update();
	
	// UI�̺�Ʈ üũ
	CUIMgr::GetInst()->update();

	//============
	// Rendering
	//============
	// ȭ�� Ŭ���� �� Rectangle
	Rectangle(m_pMemTex->GetDc(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	// back DC�� render�� ��-------------------------------
	CSceneMgr::GetInst()->render(m_pMemTex->GetDc()); // ������Ʈ�� ����
	CCamera::GetInst()->render(m_pMemTex->GetDc()); // ī�޶� ȿ�� ����
	// ---------------------------------------------------

	
	
	// main DC�� Back DC�� �׷��ش�--------------------------------------------
	//���� CPU�� ó�� ����, �ݺ����̰� �ܼ��� �۾���, windowAPI�� CPU�� �̿��ؼ� ó�����ִ� �Լ��� ����
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDc(), 0, 0, SRCCOPY);
	// -----------------------------------------------------------------------

	//============
	// Ÿ�� �Ŵ��� ���� / window ��ܿ� �����Ӽ� ǥ��
	//============
	CTimeMgr::GetInst()->render();


	//================
	// �̺�Ʈ ����ó��
	//================
	CEventMgr::GetInst()->update();


}

void Core::CreateBrushPen()
{
	// ��� �̹� ��ü������ �����쿡�� ������� �츮�� ������ ���� ����
	// �����쿡�� ����� ���� ������ ���� �츮�� �������� �ʾƵ� �˴ϴ�.
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// red, blue, green pen / pen���� �̹� ����������� ���� ���� �ƶ� �����������
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB( 0, 0, 255));
}




#include "pch.h"
#include "CTimeMgr.h"
#include "Core.h"

CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	, m_llPreCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//���� ī��Ʈ
	QueryPerformanceCounter(&m_llPreCount);
	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	//dt�� �������ӿ� �ɸ��� �ð��̴�, dt�� ���� �ʴ� ������ ��
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPreCount.QuadPart) / (double)m_llFrequency.QuadPart;
	// ����ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPreCount = m_llCurCount;
	
#ifdef _DEBUG
	if (m_dDT > (1. / 60))
		m_dDT = (1. / 60); 

#endif

	
}

void CTimeMgr::render()
{
	++m_iCallCount;  // ȣ��Ƚ�� ����
	m_dAcc += m_dDT; // DT ����



	// dt�� 1���̻� �����Ǹ� m_iCallCount�� ȣ��Ƚ���� ������ ���� ��
	if (m_dAcc >= 1.) {
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,  DT : %f", m_iFPS, m_dDT);
		SetWindowText(Core::GetInst()->GetMainHwnd(), szBuffer);
	}
}

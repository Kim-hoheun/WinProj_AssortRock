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
	//현재 카운트
	QueryPerformanceCounter(&m_llPreCount);
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	//dt는 한프레임에 걸리는 시간이다, dt의 역은 초당 프레임 수
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPreCount.QuadPart) / (double)m_llFrequency.QuadPart;
	// 이전카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPreCount = m_llCurCount;
	
#ifdef _DEBUG
	if (m_dDT > (1. / 60))
		m_dDT = (1. / 60); 

#endif

	
}

void CTimeMgr::render()
{
	++m_iCallCount;  // 호출횟수 누적
	m_dAcc += m_dDT; // DT 누적



	// dt가 1초이상 누적되면 m_iCallCount의 호출횟수가 프레임 수가 됨
	if (m_dAcc >= 1.) {
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,  DT : %f", m_iFPS, m_dDT);
		SetWindowText(Core::GetInst()->GetMainHwnd(), szBuffer);
	}
}

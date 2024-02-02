#include "pch.h"
#include "CColider.h"
#include "CObject.h"
#include "Core.h"
#include "SelectGDI.h"
#include "CCamera.h"

UINT CColider::g_iNextID = 0;

CColider::CColider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

CColider::CColider(const CColider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{
} 

CColider::~CColider()
{
}

void CColider::finalupdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
	assert(0 <= m_iCol);
}

void CColider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_dc, ePen);
	SelectGDI d(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);
	
	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));

	

	
}

void CColider::OnCollision(CColider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CColider::OnCollisionEnter(CColider* _pOther)
{

	++m_iCol; // 세명이 충돌했을 때 0이상이어야지 로직이 발생, 만약 true false로 한다면 3개 이상일 때 문제가 생김
	m_pOwner->OnCollisionEnter(_pOther);
}

void CColider::OnCollisionExit(CColider* _pOther)
{
	
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}



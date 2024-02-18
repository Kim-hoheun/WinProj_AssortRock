#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CColider.h"
#include "CAnimator.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pColider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pColider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	
{
	if (_origin.m_pColider)
	{
		m_pColider = new CColider(*_origin.m_pColider); //콜라이더를 복사생성자로 생성하고
		m_pColider->m_pOwner = this;                    // 새로 생성한 콜라이더를 연결
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator); //콜라이더를 복사생성자로 생성하고
		m_pAnimator->m_pOwner = this;                    // 새로 생성한 콜라이더를 연결
	}
}

CObject::~CObject()
{
	if (nullptr != m_pColider)
		delete m_pColider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}



void CObject::update()
{
	
}

void CObject::finalupdate()
{
	if (m_pColider)
	{
		m_pColider->finalupdate();
	}
	
	if (m_pAnimator)
	{
		m_pAnimator->finalupdate();
	}
}

void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc
		, (int)vRenderPos.x - m_vScale.x / 2.f
		, (int)vRenderPos.y - m_vScale.y / 2.f
		, (int)vRenderPos.x + m_vScale.x / 2.f
		, (int)vRenderPos.y + m_vScale.y / 2.f);
	
	component_render(_dc);
	
}

void CObject::component_render(HDC _dc)
{
	if (nullptr != m_pColider)
	{
		m_pColider->render(_dc);
	}

	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}
}

void CObject::CreateColider()
{
	m_pColider = new CColider;
	m_pColider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

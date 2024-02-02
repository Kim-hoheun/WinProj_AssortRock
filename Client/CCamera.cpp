#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "Core.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	:m_pTargetObj(nullptr)
	, m_fTime(2.f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
{

}

CCamera::~CCamera()
 {

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}	
	}
	// ȭ�� �߾���ǥ�� ī�޶� LooAt ��ǥ���� ���̰� ���
	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;
	
	CalDiff();
}

void CCamera::CalDiff()
{
	// ���� LookAt�� ���� LooK�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLooAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt; // ���� �̵��� ����
		m_vCurLooAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
	}
	
	

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLooAt - vCenter;
	m_vPrevLookAt = m_vCurLooAt;
}

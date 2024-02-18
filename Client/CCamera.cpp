#pragma once
#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "Core.h"

#include "Core.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	:m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_vDiff{}
	, m_vLookAt{}
	, m_pVeilTex(nullptr)
{
	
}

CCamera::~CCamera()
 {

}


void CCamera::init()
{
	Vec2 vResolution = Core::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CaneraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
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

// FadeIn�� FadeOut�� �׷��ش�
void CCamera::render(HDC _dc)
{
	//  FadeIn�� FadeOut ��û�� ���ٸ� �׸��� �ʴ´�
	if (m_listCamEffect.empty())
		return;
	
	//===================
	// ��ó��
	//===================
	
	// List�� ���� effect �Ǿ��� �����´�
	tCamEffect& effect = m_listCamEffect.front();

	// �ð� �������� �����Ѵ� //fDT�� �������ӿ� �ɸ��� �ð����� �����ؼ� �ð������� ����Ѵ�
	effect.fCurTime += fDT;



	float fRatio = 0.f; // ����Ʈ ���� ����
	fRatio = effect.fCurTime / effect.fDuration;

	// ���� �ð���ŭ �������ִ°� �ڵ尡 �������༭ ���� ��ŭ �׷��ֱ�� ��
	// �ð��� ���� �ʰ��ص� �׷��� �ű� ������ ���� ������ �ʰ��� �� �־ ��������
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	// ���� 0~255 * ������� �� ���ؼ� Alpah���� ����
	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		
		iAlpha = (int)(255.f * fRatio);
		
	}
	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	
	//=================
	//Rendering
	//=================
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0; // source �� ���İ�
	bf.SourceConstantAlpha = iAlpha; // ��������, ��ü������ ���İ��� �ѹ��� �����Ѵ�

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDc()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);
	
	
	//==================
	// effect switching
	//==================

	// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���
	if (effect.fDuration < effect.fCurTime)
	{
		// ȿ�� ����
		m_listCamEffect.pop_front();
	}
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

		if (!vLookDir.IsZero()) // vLookDir�� 0,0 ������ ���� �ִµ� 0,0�� Normalize�ϸ� ������ �߱� ������ ����ó��
		{
			m_vCurLooAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}

		
	}
	
	

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLooAt - vCenter;
	m_vPrevLookAt = m_vCurLooAt;
}

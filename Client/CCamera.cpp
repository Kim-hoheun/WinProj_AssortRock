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
	// 화면 중앙좌표와 카메라 LooAt 좌표간의 차이값 계산
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

// FadeIn과 FadeOut을 그려준다
void CCamera::render(HDC _dc)
{
	//  FadeIn과 FadeOut 요청이 없다면 그리지 않는다
	if (m_listCamEffect.empty())
		return;
	
	//===================
	// 전처리
	//===================
	
	// List에 들어온 effect 맨앞을 가져온다
	tCamEffect& effect = m_listCamEffect.front();

	// 시간 누적값을 저장한다 //fDT는 한프레임에 걸리는 시간으로 누적해서 시간값으로 사용한다
	effect.fCurTime += fDT;



	float fRatio = 0.f; // 이펙트 진행 비율
	fRatio = effect.fCurTime / effect.fDuration;

	// 넘은 시간만큼 고정해주는건 코드가 복잡해줘서 넘은 만큼 그려주기로 함
	// 시간이 조금 초과해도 그려줄 거기 때문에 값이 범위를 초과할 수 있어서 보정해줌
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	// 투명도 0~255 * 진행비율 을 곱해서 Alpah값을 저장
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
	bf.AlphaFormat = 0; // source 의 알파값
	bf.SourceConstantAlpha = iAlpha; // 전역알파, 전체적으로 알파값을 한번더 적용한다

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

	// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
	if (effect.fDuration < effect.fCurTime)
	{
		// 효과 종료
		m_listCamEffect.pop_front();
	}
}

void CCamera::CalDiff()
{
	// 이전 LookAt과 현재 LooK의 차이값을 보정해서 현제의 LookAt을 구한다

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLooAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt; // 내가 이동할 방향

		if (!vLookDir.IsZero()) // vLookDir이 0,0 백터일 수도 있는데 0,0을 Normalize하면 오류가 뜨기 때문에 예외처리
		{
			m_vCurLooAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}

		
	}
	
	

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLooAt - vCenter;
	m_vPrevLookAt = m_vCurLooAt;
}

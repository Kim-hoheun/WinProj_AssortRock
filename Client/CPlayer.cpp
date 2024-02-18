#pragma once
#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CScene.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CColider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	// Texture �ε��ϱ�
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player_final.bmp");

	CreateColider();
	GetColider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetColider()->SetScale(Vec2(30.f, 50.f));

	CTexture * pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_6.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f,10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	
}

CPlayer::~CPlayer()
{
	
}
void CPlayer::update()
{
	Vec2 vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT; 
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Player_final_2.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	int iWidth = (float)pTex->Width();
	int iHeight = (float)pTex->Height();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127; // ��������, ��ü������ ���İ��� �ѹ��� �����Ѵ�

	AlphaBlend(_dc
		, int(vPos.x - iWidth / 2.f)
		, int(vPos.y - iHeight / 2.f)
		, int(iWidth) , int(iHeight)
		, pTex->GetDc()
		, 0, 0, int(iWidth), int(iHeight)
		, bf);

	//int iWidth = (int)m_pTex->Width(); // ������ ���� �� �ְ� int�� �ٲ���
	//int iHeight = (int)m_pTex->Height();// ���⵵ ��������, �ȼ����̶� �ݵ�� �������, �̰� ������ ����� �� �»�� ���� ������ ���� ���־���ؼ� �׷�
	//
	//Vec2 vPos = GetPos();

	
	/*BitBlt(_dc
		,int(vPos.x - (float)(iHeight / 2))
		,int(vPos.y - (float)(iWidth / 2))
		, iWidth, iHeight
	    , m_pTex->GetDc()
	    , 0, 0, SRCCOPY);*/

	/*TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDc()
		, 0, 0, iWidth, iHeight
	    , RGB(255, 0, 255) );*/

	// ������Ʈ(�浹ü, etc...) �� �ִ� ��� ����
	
	
	//component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissile = GetPos();
	vMissile.y -= GetScale().y / 2.f;

	//Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissile);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
	/*CScene* pCurSc = CSceneMgr::GetInst()->GetCurScene();
	pCurSc->AddObject(pMissile, GROUP_TYPE::DEFAULT);*/
}





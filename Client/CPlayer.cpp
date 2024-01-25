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

CPlayer::CPlayer()
{
	// Texture �ε��ϱ�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player_final.bmp");

	
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
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width(); // ������ ���� �� �ְ� int�� �ٲ���
	int iHeight = (int)m_pTex->Height();// ���⵵ ��������, �ȼ����̶� �ݵ�� �������, �̰� ������ ����� �� �»�� ���� ������ ���� ���־���ؼ� �׷�
	
	Vec2 vPos = GetPos();

	
	/*BitBlt(_dc
		,int(vPos.x - (float)(iHeight / 2))
		,int(vPos.y - (float)(iWidth / 2))
		, iWidth, iHeight
	    , m_pTex->GetDc()
	    , 0, 0, SRCCOPY);*/

	TransparentBlt(_dc
		, int(vPos.x - (float)(iHeight / 2))
		, int(vPos.y - (float)(iWidth / 2))
		, iWidth, iHeight
		, m_pTex->GetDc()
		, 0, 0, iWidth, iHeight
	    , RGB(255, 0, 255) );
}

void CPlayer::CreateMissile()
{
	Vec2 vMissile = GetPos();
	vMissile.y -= GetScale().y / 2.f;

	//Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissile);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(-1.f, -7.f));

	CScene* pCurSc = CSceneMgr::GetInst()->GetCurScene();
	pCurSc->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}





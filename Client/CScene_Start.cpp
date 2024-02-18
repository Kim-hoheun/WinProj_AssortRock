#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"
#include "CObject.h"
#include "CMonster.h"
#include "Core.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include"CSceneMgr.h"
#include "CCamera.h"

CScene_Start::CScene_Start()
{
}
CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update(); //������Ʈ���� ���� ��ġ�� ���� ������Ʈ

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	//���� ��ġ�� ������� ���� ��ġ�� ����
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// Object �߰�----------
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f)); 
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	// Object �߰�----------
	
	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

//	CCamera::GetInst()->SetTarget(pObj);
	
	// ���� ��ġ---------------------------------
	int iMonCount = 2;     // ������
	float fMoveDist = 25.f; // �̵��Ÿ�
	float fObjScale = 50.f; // ũ��

	// �ھ�� �ػ� ���� �������� POINT -> Vec2 ���翬���� ���
	Vec2 vResolution = Core::GetInst()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist+ fObjScale / 2.f) * 2)) / (float)(iMonCount-1);
	
	CMonster* pMonsterObj = nullptr;
	

	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object �߰�
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) +(float)i*fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}
	// ���� ��ġ--------------------------------- 

	//Ÿ�� �ε�
	//LoadTile(L"Tile\\Start.tile");


	// �浹 ����
	// Player �׸��� Moster �׷� ���� �浹üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//Vec2 vResolution = Core::GetInst()->GetResolution();
	
	// Camera Lock ����
	CCamera::GetInst()->SetLookAt(vResolution/ 2.f);

	// Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
} 

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
}

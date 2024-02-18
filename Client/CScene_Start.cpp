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
	CScene::update(); //오브젝트들의 실제 위치를 전부 업데이트

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	//실제 위치를 기반으로 랜더 위치를 수정
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// Object 추가----------
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f)); 
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	// Object 추가----------
	
	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

//	CCamera::GetInst()->SetTarget(pObj);
	
	// 몬스터 배치---------------------------------
	int iMonCount = 2;     // 마리수
	float fMoveDist = 25.f; // 이동거리
	float fObjScale = 50.f; // 크기

	// 코어에서 해상도 값을 가져왔음 POINT -> Vec2 복사연산자 사용
	Vec2 vResolution = Core::GetInst()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist+ fObjScale / 2.f) * 2)) / (float)(iMonCount-1);
	
	CMonster* pMonsterObj = nullptr;
	

	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object 추가
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) +(float)i*fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}
	// 몬스터 배치--------------------------------- 

	//타일 로딩
	//LoadTile(L"Tile\\Start.tile");


	// 충돌 지정
	// Player 그릅과 Moster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//Vec2 vResolution = Core::GetInst()->GetResolution();
	
	// Camera Lock 지원
	CCamera::GetInst()->SetLookAt(vResolution/ 2.f);

	// Camera 효과 지원
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
} 

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
}

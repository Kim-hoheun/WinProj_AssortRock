#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"
#include "CObject.h"
#include "CMonster.h"
#include "Core.h"
#include "CTexture.h"
#include "CPathMgr.h"

CScene_Start::CScene_Start()
{
}
CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object 추가----------
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);
	// Object 추가----------
	
	
	// 몬스터 배치---------------------------------
	int iMonCount = 16;     // 마리수
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
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) +(float)i*fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
	// 몬스터 배치---------------------------------
}

void CScene_Start::Exit()
{
}

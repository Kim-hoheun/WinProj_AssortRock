#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CTile.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 백터의 j 물체 삭제
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// update에서는 삭제예정 오브젝트는 업데이트 해주지 않지만
			// finalupdate에서는 충돌을 마무리 하기 위해서 finalupdate를 해줘야 한다
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// for(초기식, 조건식, 변화식) 인데 세개다 생략이 가능함 ㄹㅇㅋㅋ..
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end(); )
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]); -> 로 해도 컴파일러가 아라서 처리해주나 밑에 처럼 쓰는게 정석이다
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]); 
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE3.bmp");

	// 타일 생성
	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	//FILE도 결국 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// 타일 가로 세로 개수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;
	
	// 저장해둔 순서대로 읽으면 문제가 없음
	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// 불러온 개수에 맞게 EmptyTile 을 만들어두기
	CreateTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);


	// 타일의 인덱스 정보를 로드해옴
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

#include "pch.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);

}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 동일한 Key값이 있는지 확인하고
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) {
		return pTex;
	}

	// 파일로 부터 로딩되기 때문에 경로를 가져온다
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// Texture 생성하고
	pTex = new CTexture;
	// Path를 이용해서 비트맵위에 이미지 올리고 dc를 생성
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	// 텍스쳐를 map에 저장
	m_mapTex.insert(make_pair(_strKey, pTex));


	return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT iWidth, UINT iHieght)
{
	// 동일한 Key값이 있는지 확인하고
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) {
		return pTex;
	}
	// 파일로 부터 로딩되는 것이 아님

	// Texture 생성하고
	pTex = new CTexture;
	// Path를 이용해서 비트맵위에 이미지 올리고 dc를 생성
	pTex->Create(iWidth, iHieght);
	pTex->SetKey(_strKey);
	
	// 텍스쳐를 map에 저장
	m_mapTex.insert(make_pair(_strKey, pTex));


	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);
	
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}

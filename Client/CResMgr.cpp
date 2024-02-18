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
	// ������ Key���� �ִ��� Ȯ���ϰ�
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) {
		return pTex;
	}

	// ���Ϸ� ���� �ε��Ǳ� ������ ��θ� �����´�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// Texture �����ϰ�
	pTex = new CTexture;
	// Path�� �̿��ؼ� ��Ʈ������ �̹��� �ø��� dc�� ����
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	// �ؽ��ĸ� map�� ����
	m_mapTex.insert(make_pair(_strKey, pTex));


	return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT iWidth, UINT iHieght)
{
	// ������ Key���� �ִ��� Ȯ���ϰ�
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) {
		return pTex;
	}
	// ���Ϸ� ���� �ε��Ǵ� ���� �ƴ�

	// Texture �����ϰ�
	pTex = new CTexture;
	// Path�� �̿��ؼ� ��Ʈ������ �̹��� �ø��� dc�� ����
	pTex->Create(iWidth, iHieght);
	pTex->SetKey(_strKey);
	
	// �ؽ��ĸ� map�� ����
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

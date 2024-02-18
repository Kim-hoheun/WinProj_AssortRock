#include "pch.h"
#include "CPathMgr.h"
#include "Core.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	// 상위 폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	// +bin\\content \\ 
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
	//SetWindowText(Core::GetInst()->GetMainHwnd(), m_szContentPath);
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filePath)
{
	wstring strFilePath = _filePath;

	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFileLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFileLen - iAbsLen);

	return strRelativePath;
}

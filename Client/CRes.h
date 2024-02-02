#pragma once
class CRes
{

private:
	wstring m_strKey; // 리소스 만의 고유한 ID
	wstring m_strRelativePath; // 리소스 상대경로

public:
	void SetKey(const wstring& _strKeyk) { m_strKey = _strKeyk ; }
	void SetRelativePath(wstring _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();
};


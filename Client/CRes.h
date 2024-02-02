#pragma once
class CRes
{

private:
	wstring m_strKey; // ���ҽ� ���� ������ ID
	wstring m_strRelativePath; // ���ҽ� �����

public:
	void SetKey(const wstring& _strKeyk) { m_strKey = _strKeyk ; }
	void SetRelativePath(wstring _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();
};


#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_szContentPath[256];
	wchar_t m_szRelativePath[256];
public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

	// 절대경로가 들어오면 뒷부분을 잘라서 상대경로로 반환해줌
	wstring GetRelativePath(const wchar_t* _filePath);
};


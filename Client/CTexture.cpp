#include "pch.h"
#include "CTexture.h"
#include "Core.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 함수에 들어가는 경로값은 절대경로이다
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);


	// 비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	
	
	//비트 맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);
	
	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP),&m_bitInfo);




	
}

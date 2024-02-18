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

void CTexture::Create(UINT _iWidth, UINT _iHeigth)
{
	HDC maindc = Core::GetInst()->GetMainDC();
	
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeigth);
	m_dc = CreateCompatibleDC(maindc);

	// DC를 처음에 만들 때 1픽셀 짜리 비트맵을 가춰서 나옴 그래서 delete해서 지워버림
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}

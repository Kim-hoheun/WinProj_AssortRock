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
	// �Լ��� ���� ��ΰ��� �������̴�
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);


	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	
	
	//��Ʈ �ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);
	
	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP),&m_bitInfo);




	
}

void CTexture::Create(UINT _iWidth, UINT _iHeigth)
{
	HDC maindc = Core::GetInst()->GetMainDC();
	
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeigth);
	m_dc = CreateCompatibleDC(maindc);

	// DC�� ó���� ���� �� 1�ȼ� ¥�� ��Ʈ���� ���缭 ���� �׷��� delete�ؼ� ��������
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}

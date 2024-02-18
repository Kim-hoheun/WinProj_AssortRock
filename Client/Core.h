#pragma once
class CTexture;

class Core { 
	SINGLE(Core)
private:
	HWND m_hwnd;          // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC;			  // ���� �����쿡 Draw �� DC1

	CTexture* m_pMemTex;  // ����� �ؽ���
	//HBITMAP m_hBit;		  // ������۸��� �ʿ��� ��Ʈ��
	//HDC m_memDC;          // ������۸��� �ʿ��� DC2

	// ���� ����ϴ� GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN   m_arrPen[(UINT)PEN_TYPE::END];


public:
	int init(HWND hwnd, POINT _ptResolution);
	void progress();
private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hwnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT) _eType]; }
	
};

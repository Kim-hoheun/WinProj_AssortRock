#pragma once
class CTexture;

class Core { 
	SINGLE(Core)
private:
	HWND m_hwnd;          // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC;			  // 메인 윈도우에 Draw 할 DC1

	CTexture* m_pMemTex;  // 백버퍼 텍스쳐
	//HBITMAP m_hBit;		  // 더블버퍼링에 필요한 비트맵
	//HDC m_memDC;          // 더블버퍼링에 필요한 DC2

	// 자주 사용하는 GDI Object
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

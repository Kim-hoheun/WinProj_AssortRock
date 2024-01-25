#pragma once

class Core { 
	SINGLE(Core)
private:
	HWND m_hwnd;          // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC;			  // 메인 윈도우에 Draw 할 DC1

	HBITMAP m_hBit;		  // 더블버퍼링에 필요한 비트맵
	HDC m_memDC;          // 더블버퍼링에 필요한 DC2

public:
	int init(HWND hwnd, POINT _ptResolution);
	void progress();
private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hwnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	
};

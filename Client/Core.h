#pragma once

class Core { 
	SINGLE(Core)
private:
	HWND m_hwnd;          // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC;			  // ���� �����쿡 Draw �� DC1

	HBITMAP m_hBit;		  // ������۸��� �ʿ��� ��Ʈ��
	HDC m_memDC;          // ������۸��� �ʿ��� DC2

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

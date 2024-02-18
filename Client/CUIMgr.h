#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_FocusedUI; // 원래는 모든 부모UI가 이벤트를 받아갔지만(둘다 이벤트를 받아 둘이 동시에 클릭되서 동시에 움직이는 문제가생김)
					  // focusedUI 변수를 통해 포커싱 중인 UI만 이벤트를 받아가게 설계

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

private:
	
	CUI* GetFoucusedUI();
	// 부모 UI내에서 실제로 타겟팅 된 UI를 찾아서 반환한다
	CUI* GetTargetedUI(CUI* _pParentUI); 

};


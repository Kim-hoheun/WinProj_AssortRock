#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_FocusedUI; // ������ ��� �θ�UI�� �̺�Ʈ�� �޾ư�����(�Ѵ� �̺�Ʈ�� �޾� ���� ���ÿ� Ŭ���Ǽ� ���ÿ� �����̴� ����������)
					  // focusedUI ������ ���� ��Ŀ�� ���� UI�� �̺�Ʈ�� �޾ư��� ����

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

private:
	
	CUI* GetFoucusedUI();
	// �θ� UI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�
	CUI* GetTargetedUI(CUI* _pParentUI); 

};


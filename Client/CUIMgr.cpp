#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUIMgr::CUIMgr()
	: m_FocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	

	 //1. FocusedUI ����, ����Ǿ����� Ȯ���غ���
	m_FocusedUI = GetFoucusedUI();

	// �̺�Ʈ ó���� �� UI�� ���ٸ� nullptr�� ��ȯ�Ǿ� �ؿ� if���� �ɸ��Ե�
	if (!m_FocusedUI)
		return;

	// 2. focusedUI���� �̺�Ʈ üũ
	// ��� UI�� �̺�Ʈ�� �ݸ����� �޾ư��� �ʰ� ��Ŀ�̵� UI�� �̺�Ʈ�� �޾ư���
	// �θ���� �ڽı��� ���� TargetUI�� ã�ƿ�
	CUI* pTargetUI = GetTargetedUI(m_FocusedUI);
	bool bLbtAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	

	if (nullptr != pTargetUI) {
		pTargetUI->MouseOn();

		if (bLbtnTap)//���� ���콺 Ŭ���ߴ°�?
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtAway) // ���� ���콺 Ŭ���� �ô°�?
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown = true)
			{
				pTargetUI->MouseLbtnClicked();
			}

			// ���ʹ�ư ���� , ���ȴ� üũ�� �ٽ� �����Ѵ�
			pTargetUI->m_bLbtnDown = false;
		}
	}
}
void CUIMgr::SetFocusedUI(CUI* _pUI)

{
	// �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
	if (m_FocusedUI == _pUI || nullptr == _pUI)
	{
		m_FocusedUI = _pUI;
		return;
	}
	m_FocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	
	//���Ǹ� ���� iterator�� �����س�
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end(); ++iter)
	{
		if (m_FocusedUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_FocusedUI);
}
// ��Ŀ�� �� UI�� �� ���� �׷����� ���ͳ� ������ �ٲٰ� ��Ŀ�̵� UI�� �����ϴ� �Լ�
CUI* CUIMgr::GetFoucusedUI()
{
	// �θ�鰣�� ���� ��Ŀ���� �Ǿ� �ִ��� ã�ƿ��� �Լ�
	// ������� UI������Ʈ���� �����´�
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�
	CUI* pFocusedUI = m_FocusedUI;

	if (!bLbtnTap)//���� ���콺 Ŭ���ߴ°�?
	{
		return pFocusedUI;
	}

	// ���ʹ�ư TAP�� �߻��ߴٴ� ����
	vector<CObject*>::iterator targetiter = vecUI.end(); // ���Ϳ��� �����ϰ� �ǵڷ� ������� �ؼ�
										   //���Ǹ� ���� iterator�� �����س�
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// �̹��� Focus �� UI�� ����
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// ���� ������ �� �ڷ� ���� ��ü -> ������ ������ �ڷ� �� ���� ���� ���� �׷����� ������ �ǵڷ� ����

	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtAway = KEY_AWAY(KEY::LBTN);

	
	
	// 1. �θ� UI ���� , ��� �ڽĵ��� �˻��Ѵ�.
	
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;			// ���� ���� ���Ƽ� ���������� ����
	static vector<CUI*> vecNoneTarget;	// ���� ���� ���Ƽ� ���������� ����

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI); // �θ� UI�� ť�� ����

	while (!queue.empty()) // ť�� �� �������� �ݺ�
	{
		CUI* pUI = queue.front(); // ���������� ������ ��� ����
		queue.pop_front();		  // ť���� ����

		// 2. Ÿ�� UI�� ��, �� �켱������ ���� ������ ���� ������ �ڽ� UI
		// ť���� ������ UI�� target ���� Ȯ��
		// �ش� UI�� ���콺�� �ö� �ִٸ� TargetUI�� �־��ְ� �ڽİ����� Ž���Ϸ���-> Level Ž������
		if (pUI->IsMouseOn())
		{
			// TargetUI�� ��ٸ� �ٲ�� ���� UI�� ���ؼ� m_blbtnDown = false; ����� �� ������ ���Ϳ� �־���
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else {

			vecNoneTarget.push_back(pUI); 
			
		}

		// target���� �˻��� �˻��� UI�� �ڽİ�ü���� ���� ť�� ����
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
		
	}
	// target UI�� ������ �������鸸 falseó��
	if (bLbtAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			// ���ʹ�ư ���� , ���ȴ� üũ�� �ٽ� �����Ѵ�
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}
	

	return pTargetUI;
}

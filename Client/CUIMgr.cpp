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
	

	 //1. FocusedUI 인지, 변경되었는지 확인해보기
	m_FocusedUI = GetFoucusedUI();

	// 이벤트 처리해 줄 UI가 없다면 nullptr이 반환되어 밑에 if문에 걸리게됨
	if (!m_FocusedUI)
		return;

	// 2. focusedUI에게 이벤트 체크
	// 모든 UI가 이벤트를 반목문으로 받아가지 않고 포커싱된 UI만 이벤트를 받아간다
	// 부모부터 자식까지 실제 TargetUI를 찾아옴
	CUI* pTargetUI = GetTargetedUI(m_FocusedUI);
	bool bLbtAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	

	if (nullptr != pTargetUI) {
		pTargetUI->MouseOn();

		if (bLbtnTap)//왼쪽 마우스 클릿했는가?
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtAway) // 왼쪽 마우스 클릭을 뗐는가?
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown = true)
			{
				pTargetUI->MouseLbtnClicked();
			}

			// 외쪽버튼 떼면 , 눌렸던 체크를 다시 해제한다
			pTargetUI->m_bLbtnDown = false;
		}
	}
}
void CUIMgr::SetFocusedUI(CUI* _pUI)

{
	// 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
	if (m_FocusedUI == _pUI || nullptr == _pUI)
	{
		m_FocusedUI = _pUI;
		return;
	}
	m_FocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	
	//편의를 위해 iterator를 저장해놈
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
// 포커싱 된 UI가 맨 위에 그려지게 백터내 순서도 바꾸고 포커싱된 UI를 리턴하는 함수
CUI* CUIMgr::GetFoucusedUI()
{
	// 부모들간에 누가 포커싱이 되어 있는지 찾아오는 함수
	// 현재씬의 UI오브젝트들을 가져온다
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다
	CUI* pFocusedUI = m_FocusedUI;

	if (!bLbtnTap)//왼쪽 마우스 클릿했는가?
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 TAP이 발생했다는 전제
	vector<CObject*>::iterator targetiter = vecUI.end(); // 백터에서 삭제하고 맨뒤로 보내줘야 해서
										   //편의를 위해 iterator를 저장해놈
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 이번에 Focus 된 UI가 없다
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 백터 내에서 맨 뒤로 순번 교체 -> 랜더링 순서가 뒤로 갈 수록 제일 위에 그려지기 때문에 맨뒤로 보냄

	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtAway = KEY_AWAY(KEY::LBTN);

	
	
	// 1. 부모 UI 포함 , 모든 자식들을 검사한다.
	
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;			// 자주 쓸거 같아서 정적변수로 선언
	static vector<CUI*> vecNoneTarget;	// 자주 쓸거 같아서 정적변수로 선언

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI); // 부모 UI를 큐에 삽입

	while (!queue.empty()) // 큐가 다 빌때까지 반복
	{
		CUI* pUI = queue.front(); // 지역변수에 추출할 요소 저장
		queue.pop_front();		  // 큐에서 추출

		// 2. 타켓 UI들 중, 더 우선순위가 높은 기준은 낮은 계층의 자식 UI
		// 큐에서 꺼내온 UI가 target 인지 확인
		// 해당 UI에 마우스가 올라가 있다면 TargetUI에 넣어주고 자식계층을 탐색하러감-> Level 탐색을함
		if (pUI->IsMouseOn())
		{
			// TargetUI가 뀐다면 바뀌기 전에 UI에 대해서 m_blbtnDown = false; 해줘야 함 떄문에 백터에 넣어줌
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else {

			vecNoneTarget.push_back(pUI); 
			
		}

		// target인지 검사후 검사한 UI의 자식객체들을 전부 큐에 삽입
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
		
	}
	// target UI를 제외한 나머지들만 false처리
	if (bLbtAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			// 외쪽버튼 떼면 , 눌렸던 체크를 다시 해제한다
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}
	

	return pTargetUI;
}

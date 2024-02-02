#pragma once
//전방선언
class CObject; // 전방선언 하는 이유
			   // 헤더를 참조하면 CObject코드가 수정될 떄 마다 여기도 컴파일 해줘야함
			   // 전방선언만 한다면 CObject쪽에서 수정이 일어나도 Scene에서는 재컴파일을 하지 않음
               // 헤더가 아닌 전방선언을 한 경우 포인터로만 선언이 가능하다

class CScene
{ 
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	wstring          m_strName; // Scene 이름

public:
	void SetName(const wstring& _strName){ m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0;  // 해당 Scene에서 탈출 시 호출

	// 클래스는 헤더에 구현 하면 인라인 함수처리됨
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT) _eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

public:
	CScene();
	virtual ~CScene();
	
};


#pragma once
class CObject;

class CColider
{
private:
	static UINT  g_iNextID;
	CObject*	 m_pOwner;     // Colider를 소유하고 있는 오브젝트
	Vec2	     m_vOffsetPos; // 오브젝트로 부터 상대적인 거리
	Vec2		 m_vFinalPos;  // finalupdate 에서 매 프레임마다 계산

	Vec2         m_vScale;     // 충돌체의 크기

	UINT         m_iID;        // 충돌체 고유한 ID 값
	int		     m_iCol;       // 세명이 충돌했을 때 0이상이어야지 로직이 발생, 만약 true false로 한다면 3개 이상일 때 문제가 생김
	

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos;  }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return  m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(CColider* _pOther);      // 충돌 중인 경우 호출 되는 함수
	void OnCollisionEnter(CColider* _pOther); // 충돌 진입 시
	void OnCollisionExit(CColider* _pOther);  // 충돌 해제 시


	CColider& operator = (CColider& _origin) = delete; // 기본연산자 생성 금지

	

public:
	CColider();
	CColider(const CColider& _origin);
	~CColider();
	

	friend class CObject;

};


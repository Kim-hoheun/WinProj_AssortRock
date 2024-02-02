#pragma once
#include "CCamera.h" //원래 헤더에서 헤더를 참조를 잘안하려하지만 모든 오브젝트가 카메라를 써야하기 때문에 참조

class CColider;
class CAnimator;

class CObject
{
private:
	wstring m_strName;


	Vec2 m_vPos;
	Vec2 m_vScale;

	// Component
	CColider* m_pColider;
	CAnimator* m_pAnimator;

	bool m_bAlive; // 자신의 상태가 dead인지 체크하는 변수 / dead라면 삭제예정이다

public:
	void SetPos(Vec2 _vPos)		{ m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos()				{ return m_vPos; }
	Vec2 GetScale()				{ return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	CColider* GetColider()		{ return m_pColider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

	bool IsDead() { return !m_bAlive; }
	

	void CreateColider();
	void CreateAnimator();


	virtual void OnCollision(CColider* _pOther) {}  // 충돌 중인 경우 호출 되는 함수
	virtual void OnCollisionEnter(CColider* _pOther) {} // 충돌 진입 시
	virtual void OnCollisionExit(CColider* _pOther) {}  // 충돌 해제 시

private:
	void SetDead() { m_bAlive = false; }


public:
	virtual void update() = 0;
	virtual void finalupdate() final; 
	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0; // 나 자신의 복사버전들 돌려주는 역할

public:
	CObject();
	CObject(const CObject&  _origin);
	virtual ~CObject();

	friend class CEventMgr; //오직 이벤트 매니저에서만 삭제상태로 바꿀 수 있음 SetDead()
};


#pragma once
#include "CCamera.h" //���� ������� ����� ������ �߾��Ϸ������� ��� ������Ʈ�� ī�޶� ����ϱ� ������ ����

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

	bool m_bAlive; // �ڽ��� ���°� dead���� üũ�ϴ� ���� / dead��� ���������̴�

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


	virtual void OnCollision(CColider* _pOther) {}  // �浹 ���� ��� ȣ�� �Ǵ� �Լ�
	virtual void OnCollisionEnter(CColider* _pOther) {} // �浹 ���� ��
	virtual void OnCollisionExit(CColider* _pOther) {}  // �浹 ���� ��

private:
	void SetDead() { m_bAlive = false; }


public:
	virtual void update() = 0;
	virtual void finalupdate() final; 
	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0; // �� �ڽ��� ��������� �����ִ� ����

public:
	CObject();
	CObject(const CObject&  _origin);
	virtual ~CObject();

	friend class CEventMgr; //���� �̺�Ʈ �Ŵ��������� �������·� �ٲ� �� ���� SetDead()
};


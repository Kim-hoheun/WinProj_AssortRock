#pragma once
class CObject;

class CColider
{
private:
	static UINT  g_iNextID;
	CObject*	 m_pOwner;     // Colider�� �����ϰ� �ִ� ������Ʈ
	Vec2	     m_vOffsetPos; // ������Ʈ�� ���� ������� �Ÿ�
	Vec2		 m_vFinalPos;  // finalupdate ���� �� �����Ӹ��� ���

	Vec2         m_vScale;     // �浹ü�� ũ��

	UINT         m_iID;        // �浹ü ������ ID ��
	int		     m_iCol;       // ������ �浹���� �� 0�̻��̾���� ������ �߻�, ���� true false�� �Ѵٸ� 3�� �̻��� �� ������ ����
	

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
	// �浹 ���� �Լ�
	void OnCollision(CColider* _pOther);      // �浹 ���� ��� ȣ�� �Ǵ� �Լ�
	void OnCollisionEnter(CColider* _pOther); // �浹 ���� ��
	void OnCollisionExit(CColider* _pOther);  // �浹 ���� ��


	CColider& operator = (CColider& _origin) = delete; // �⺻������ ���� ����

	

public:
	CColider();
	CColider(const CColider& _origin);
	~CColider();
	

	friend class CObject;

};


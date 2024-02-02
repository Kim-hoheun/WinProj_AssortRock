#pragma once
class CColider;

union COLLIER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)

private:
	map<ULONGLONG, bool> m_mapColInfo;						//�浹ü ���� ���� ������ �浹 ����
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END]; // �׷찣�� �浹 üũ ��Ʈ����

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CColider* _pLeftCol, CColider* _pRightCol);
};


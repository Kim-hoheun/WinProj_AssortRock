#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{
public:
	virtual void update();
	virtual void Enter(); // �̹� �θ��ʿ��� �����Լ��� �����س��� ���� ��� ������ �����Լ��� �ƴ�
	virtual void Exit();

public:	
	CScene_Start();
	~CScene_Start();
	
};

#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{
public:
	virtual void update();
	virtual void Enter(); // 이미 부모쪽에서 가상함수로 선언해놔서 여긴 명시 했을뿐 가상함수가 아님
	virtual void Exit();

public:	
	CScene_Start();
	~CScene_Start();
	
};

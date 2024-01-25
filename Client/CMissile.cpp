#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	
{
	m_vDir.Normalize();
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	/*vPos.x += 200.f * fDT * cosf(m_fTheta);
	vPos.y -= 200.f * fDT * sinf(m_fTheta);*/

	vPos.x += 200.f * fDT * m_vDir.x;
	vPos.y += 200.f * fDT * m_vDir.y;


	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{ 
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_dc, (int)vPos.x - vScale.x / 2.f, (int)vPos.y - vScale.y / 2.f
		, (int)vPos.x + vScale.x / 2.f, (int)vPos.y + vScale.y / 2.f);
}

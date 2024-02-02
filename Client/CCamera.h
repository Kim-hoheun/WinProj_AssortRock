#pragma once
class CCamera
{
	SINGLE(CCamera);

private:
	Vec2	  m_vLookAt;   //카메라가 보고 있는 위치, 우리 화면의 중심이 됨
	Vec2	  m_vCurLooAt; // 이전위치와 현재위치 보정 위치
	Vec2      m_vPrevLookAt;  // 카메라가 보는 이전 프레임 위치
	


	CObject*  m_pTargetObj;// 카메라 타깃 오브젝트 : 얘를 따라서 카메라도 움직인다
	Vec2      m_vDiff;     // 해상도 중심위치와 ,카메라 LooAt 간의 차이 값


	float	  m_fTime;     // 타겟을 따라가는데 걸린 시간
	float	  m_fSpeed;	   // 타겟을 따라가는 속도
	float     m_fAccTime;  // 누적시간

public:
	void SetLookAt(Vec2 _vLook) { 
		m_vLookAt = _vLook;
		float fMoveDis = (m_vLookAt - m_vPrevLookAt).Length(); // 이동거리
		m_fSpeed = fMoveDis / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLooAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
public:
	void update();

private:
	void CalDiff();
};


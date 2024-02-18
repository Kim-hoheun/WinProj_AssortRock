#pragma once
class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect				 // fadein, fadeout을 순차적으로 요청받았을 때
{								 // 순차적으로 처리하기 위한 구조를 만들기 위해 구조체로 선언해서 List에 넣어줬다
	CAM_EFFECT eEffect;			 // 카메라 효과
	float	   fDuration;		 // 효과 진행 시간
	float	   fCurTime;		 // 카메라 효과 현재 진행된 시간
};

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

		

	list<tCamEffect>    m_listCamEffect;
	CTexture*			m_pVeilTex;			// 카메라 가림막 택스쳐
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

	void FadeIn(float _fDuration)
	{
		// FadeIn 를 구조체로 만들어 List에 넣어 순차적으로 처리한다
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		// 0으로 나누는걸 방지하기 위한 예외처리
		if (0.f == ef.fDuration)
			assert(nullptr);

		
	}
	void FadeOut(float _fDuration)
	{
		// FadeOut 를 구조체로 만들어 List에 넣어 순차적으로 처리한다
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		// 0으로 나누는걸 방지하기 위한 예외처리
		if (0.f == ef.fDuration)
			assert(nullptr);

		
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();
};


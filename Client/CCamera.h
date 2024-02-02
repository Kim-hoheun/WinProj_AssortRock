#pragma once
class CCamera
{
	SINGLE(CCamera);

private:
	Vec2	  m_vLookAt;   //ī�޶� ���� �ִ� ��ġ, �츮 ȭ���� �߽��� ��
	Vec2	  m_vCurLooAt; // ������ġ�� ������ġ ���� ��ġ
	Vec2      m_vPrevLookAt;  // ī�޶� ���� ���� ������ ��ġ
	


	CObject*  m_pTargetObj;// ī�޶� Ÿ�� ������Ʈ : �긦 ���� ī�޶� �����δ�
	Vec2      m_vDiff;     // �ػ� �߽���ġ�� ,ī�޶� LooAt ���� ���� ��


	float	  m_fTime;     // Ÿ���� ���󰡴µ� �ɸ� �ð�
	float	  m_fSpeed;	   // Ÿ���� ���󰡴� �ӵ�
	float     m_fAccTime;  // �����ð�

public:
	void SetLookAt(Vec2 _vLook) { 
		m_vLookAt = _vLook;
		float fMoveDis = (m_vLookAt - m_vPrevLookAt).Length(); // �̵��Ÿ�
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


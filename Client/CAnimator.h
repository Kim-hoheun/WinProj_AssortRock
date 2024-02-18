#pragma once
class CObject;
class CAnimation;
class CTexture;



class CAnimator
{

private:
	map<wstring, CAnimation*> m_mapAnim;    // 모든 Animation 저장
	CAnimation*				  m_pCurAnim;   // 현재 재생중인 Animation
	CObject*				  m_pOwner;     // CAnimator를 소유하고 있는 오브젝트
	bool					  m_bRepeat;     // 반복재생 여부
public:
	CObject* Getobj() { return m_pOwner; }

public:
						// 텍스처, 좌상단 정보, 걷는이미지 하나하나를 자를 크기(가로,세로), 이미지 한칸크기(가로), 하나의 애니메이션을 이루는 이미지프레임의 개수 
	void CreateAnimation(const wstring& _strName,CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};


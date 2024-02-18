#include "CBtnUI.h"




CBtnUI::CBtnUI()
	:CUI(false)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneFunc(nullptr)
	, m_pSceneInst(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}


//void CBtnUI::update()
//{
//}

void CBtnUI::MouseOn()
{
	

}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	
	if (nullptr != m_pFunc) // �Լ������Ͱ� �ʱ�ȭ�� �Ǿ��ٸ� �Լ������� m_pFunc�� ����
	{
		m_pFunc(m_param1, m_param2);
	}
	if (m_pSceneInst && m_pSceneFunc )
	{
		// ���� ȣ���� ��ü�� ������ ȣ�� *m_pSceneInst
		// ������ �����ؼ� . ����� �� �Լ������͸� �̿��� ������ ���� *m_pSceneFunc
		// �� ��ü �����ļ� �Լ� ȣ��()
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}

void CBtnUI::SetClickedCallBack(CScene* _Scene, CSCENE_MEMFUNC _pSceneFunc)
{

	m_pSceneInst = _Scene;
	m_pSceneFunc = _pSceneFunc;

}
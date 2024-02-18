  #include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"

#include "Core.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "resource.h"

#include "CUIMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CPathMgr.h"



void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}
void CScene_Tool::Enter()
{
	Vec2 vResolution = Core::GetInst()->GetResolution();
	
	//Ÿ�� �����
	CreateTile(5, 5);

	// UI�ϳ� ����� ����
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	


	CBtnUI* PBtnUI = new CBtnUI();
	PBtnUI->SetName(L"ChildUI");
	PBtnUI->SetScale(Vec2(100.f, 40.f));
	PBtnUI->SetPos(Vec2(0.f, 0.f));              //�����Լ��� �Ű������� �� ���� &�� �Ϲ������� �Ⱥٿ��� ����, ����� �ٿ������
	((CBtnUI*)PBtnUI)->SetClickedCallBack(this, (CSCENE_MEMFUNC) & CScene_Tool::SaveTileData);
												//�θ�Ÿ������ �Լ������͸� ���� �� �־ ��������� ĳ������ ����� �Ѵ�
	pPanelUI->AddChilde(PBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	////���纻 UI
 //	CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-500.f, 0.f));
	//AddObject(pClonePanel, GROUP_TYPE::UI);
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);

	//m_pUI = pClonePanel;
	
	// Camera Lock ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}


void CScene_Tool::Exit()
{
	DeleteAll();
}



void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	//if (KEY_TAP(KEY::LSHIFT))
	//{
	//	//CUIMgr::GetInst()->SetFocusedUI(m_pUI);

	//	SaveTileData();
	//}

	if (KEY_TAP(KEY::CTRL))
	{
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
		LoadTileData();
	}
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}

	
}
void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = Core::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"title";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal ��� 
	
	if (GetSaveFileName(&ofn))
	{
		
		// if�� �ȿ� �ɷ��� ���� Ȯ�� ��ư�� ��������
		SaveTile(szName); // Ÿ�� ������ �����ϴ� �Լ��� ȣ��
	}



	
}
// Ÿ�� ������ �����ϴ� �Լ� + ��� Ÿ�ϵ��� ���������� ������
void CScene_Tool::SaveTile(const wstring& _strFilePath)
{

	//FILE�� �ᱹ Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb"); // w�� �ϸ� �⺻������ ���ڿ��� ����ȴ�
												   // wb�� �ϸ� ���̳ʸ� �����ͷ� ����ȴ�
												   // ���ڿ��� �����ϸ� �о�� �� �� �ǵ��� �ٸ��� �߸� �ؼ��� �� �ֱ� ������ ���̳ʸ��� �����Ѵ�
	assert(pFile);
	
	// Ÿ�� ���μ��� ���� ����
	
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();


	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// ��� Ÿ�Ե��� ���������� ������ �����͸� �����ϰ� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};



	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = Core::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"title";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal ��� 

	if (GetOpenFileName(&ofn))
	{
		// �ٸ� �� enter���� LoadTile�� ���� ���ؼ� LoadTile�� ����θ� �Է��ϴ� ����� ����ϱ� ���ؼ�
		// �����ο��� ����θ� �����ϴ� ����� CPath���� ���
		wstring strRelativePath =  CPathMgr::GetInst()->GetRelativePath(szName);

		// ����θ� LoadTile�� �־���
		// if�� �ȿ� �ɷ��� ���� Ȯ�� ��ư�� ��������
		LoadTile(strRelativePath);
	}
}
// �ݹ��Լ��� ���� ���� �����Լ���
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}


// ============================
// Tile Count Window Proc
// ============================ �̰� ����Լ� �ƴ� �����Լ���
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) 
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);


			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam)); // �ش� Dialogâ�� �����, 2��° ���� ���� IDOK�� ��
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

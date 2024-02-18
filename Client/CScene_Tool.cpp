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
	
	//타일 만들기
	CreateTile(5, 5);

	// UI하나 만들어 보기
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	


	CBtnUI* PBtnUI = new CBtnUI();
	PBtnUI->SetName(L"ChildUI");
	PBtnUI->SetScale(Vec2(100.f, 40.f));
	PBtnUI->SetPos(Vec2(0.f, 0.f));              //전역함수를 매개변수로 줄 때는 &을 암묵적으로 안붙여도 가능, 멤버는 붙여줘야함
	((CBtnUI*)PBtnUI)->SetClickedCallBack(this, (CSCENE_MEMFUNC) & CScene_Tool::SaveTileData);
												//부모타입으로 함수포인터를 받을 수 있어도 명시적으로 캐스팅은 해줘야 한다
	pPanelUI->AddChilde(PBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	////복사본 UI
 //	CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-500.f, 0.f));
	//AddObject(pClonePanel, GROUP_TYPE::UI);
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);

	//m_pUI = pClonePanel;
	
	// Camera Lock 지정
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

	// Modal 방식 
	
	if (GetSaveFileName(&ofn))
	{
		
		// if문 안에 걸려서 들어가야 확인 버튼을 누른거임
		SaveTile(szName); // 타일 개수를 저장하는 함수를 호출
	}



	
}
// 타일 개수를 저장하는 함수 + 모든 타일들의 개인정보를 저장함
void CScene_Tool::SaveTile(const wstring& _strFilePath)
{

	//FILE도 결국 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb"); // w만 하면 기본적으로 문자열로 저장된다
												   // wb로 하면 바이너리 데이터로 저장된다
												   // 문자열로 저장하면 읽어올 때 내 의도와 다르게 잘못 해석할 수 있기 때문에 바이너리로 저장한다
	assert(pFile);
	
	// 타일 가로세로 개수 저장
	
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();


	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타입들을 개별적으로 저장할 데이터를 저장하게 함
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

	// Modal 방식 

	if (GetOpenFileName(&ofn))
	{
		// 다른 씬 enter에서 LoadTile을 쓰기 위해서 LoadTile에 상대경로를 입력하는 방식을 사용하기 위해서
		// 절대경로에서 상대경로만 추출하는 기능을 CPath에서 사용
		wstring strRelativePath =  CPathMgr::GetInst()->GetRelativePath(szName);

		// 상대경로를 LoadTile에 넣어줌
		// if문 안에 걸려서 들어가야 확인 버튼을 누른거임
		LoadTile(strRelativePath);
	}
}
// 콜백함수용 으로 만든 전역함수임
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}


// ============================
// Tile Count Window Proc
// ============================ 이거 멤버함수 아님 전역함수임
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

			EndDialog(hDlg, LOWORD(wParam)); // 해당 Dialog창이 종료됨, 2번째 인자 값은 IDOK가 들어감
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

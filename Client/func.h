#pragma once


//공통된 전역함수를 구현 하는 곳

class CObject;
// 오브젝트를 실행시켜 달라는 event를 요청함
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);


template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	// 템플릿 내부에서 enum class를 쓸거면 typename을 붙여줘야 함 iterator가 enum class임
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if(nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}



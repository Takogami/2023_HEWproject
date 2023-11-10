#pragma 
#include"TitleScene.h"
#include"ResultScene.h"

//	シーンの種類（列挙型）

enum class SceneList
{
	TITLE,
	STAGE_01,
	RESULT
};

class CSceneManager
{
private:
	

	SceneList NowScene;	//現在のシーンの状態

	TitleScene* titleS;
	ResultScene* resultS;

	bool exit = false;				//終了フラグ

public:

	CSceneManager();
	~CSceneManager();

	void Update();				//シーンの管理
	void ChangeScene(SceneList _inScene);	//シーンの変更
	void Exit();

};


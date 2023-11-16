#pragma once
#include "CSceneManager.h"
#include "CTextureLoader.h"
#include "CTerrainLoader.h"

//ゲーム全体を表すクラス
class CGame
{
public:
	//列挙型
	//画面の状態
	enum SCENE_STATE {
		NO_SCENE,
		TITLE,
		STAGE,
		RESULT,
	};

	//フェード状態
	enum FADE_STATE {
		NO_FADE,
		FADE_IN,
		FADE_OUT,
	};

	FADE_STATE fadeState = NO_FADE;

	DirectX::XMFLOAT2 cameraPos = { 0, 0 };	//カメラ位置

private:

	SCENE_STATE scene = TITLE;		//現在の画面
	SCENE_STATE newScene = NO_SCENE;

	//メンバ変数
	CSceneManager* SceneManager;

	CTextureLoader* TextureLoader;
	CTerrainLoader* TerrainLoader;

	//各画面の更新処理関数
	void UpdateTitle();		//タイトル画面

public:

	//メンバ関数
	CGame();								//初期化処理(コンストラクタ)
	void Update();							//ゲームループ毎に実行する処理を書く関数
	void SetScene(SCENE_STATE nextScene);	//シーン変更関数
	~CGame();								//終了処理(デストラクタ)
};

extern CGame* gGame;
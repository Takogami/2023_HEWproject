#pragma once
#include "CSceneManager.h"
#include "CTextureLoader.h"
#include "CTerrainLoader.h"

//ゲーム全体を表すクラス
class CGame
{
public:
	DirectX::XMFLOAT2 cameraPos = { 0, 0 };	//カメラ位置

private:
	
	/* メンバ変数 */
	CSceneManager* SceneManager;

	CTextureLoader* TextureLoader;
	CTerrainLoader* TerrainLoader;

public:

	/* メソッド */
	CGame();								//初期化処理(コンストラクタ)
	void Update();							//ゲームループ毎に実行する処理を書く関数
	~CGame();								//終了処理(デストラクタ)
};

extern CGame* gGame;
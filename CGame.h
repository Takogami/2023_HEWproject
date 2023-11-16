#pragma once

/* インクルード */
#include "CSceneManager.h"

//ゲーム全体を表すクラス
class CGame
{
private:
	
	/* メンバ変数 */

	// ゲームの根幹システム群
	// シングルトン設計であるため、システム内のデータを使用するときはGetInstanceすること
	CSceneManager* SceneManager;	// シーンマネージャ
	CTextureLoader* TextureLoader;	// テクスチャローダー
	CTerrainLoader* TerrainLoader;	// 地形データローダー

public:

	/* メソッド */
	CGame();								//初期化処理(コンストラクタ)
	void Update();							//ゲームループ毎に実行する処理を書く関数
	~CGame();								//終了処理(デストラクタ)
};

extern CGame* gGame;
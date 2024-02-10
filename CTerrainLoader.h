#pragma once

/* インクルード */
#include <vector>
#include <string>

/* マクロ定義 */

// マップを構成するオブジェクト(タイル)のサイズ
#define TILE_WIDTH		(0.15f)
#define TILE_HEIGHT		(0.15f)

// 画面左上の座標
#define ORIGIN_TILE_POS_X	(-1.924f)
#define ORIGIN_TILE_POS_Y	(1.051f)

// 地形データの識別子
enum class TERRAIN_ID
{
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
};

// CStageCreateクラス
class CTerrainLoader
{
private:
	/* メンバ変数 */

	// 唯一のインスタンスを格納するためのポインタ
	static CTerrainLoader* instance;
	// ステージデータのファイル名
	std::vector<std::string> file_name = 
	{
		"stage1_data.csv",
		"stage2_data.csv",
		"stage3_data.csv",
		"stage4_data.csv",
	};
	// 文字列連結で完成させたパスの情報を格納
	std::vector<std::string> path;
	// マップデータ保存用
	std::vector<std::vector<int>> map_info;

	/* メソッド */

	// コンストラクタ
	CTerrainLoader();
	// デストラクタ
	~CTerrainLoader();
	// アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();

public:
	/* メソッド */

	// インスタンスを取得するためのメソッド
	static CTerrainLoader* GetInstance();
	// 地形データの読み込み
	void LoadTerrainData(TERRAIN_ID stage);
	// 地形データの取得を行う
	std::vector<std::vector<int>> GetTerrainData();
};


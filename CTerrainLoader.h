#pragma once

/* インクルード */
#include <vector>
#include <string>

// 地形データの識別子
enum class TERRAIN_ID
{
	STAGE_1,
};

// CStageCreateクラス
class CTerrainLoader
{
private:
	/* メンバ変数 */

	// 唯一のインスタンスを格納するためのポインタ
	static CTerrainLoader* instance;
	// １ブロックのサイズ
	const float tile_size = 0.15f;
	// ステージデータのファイル名
	std::vector<std::string> file_name = 
	{
		"stage1_data.csv",
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


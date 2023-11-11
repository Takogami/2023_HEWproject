/* インクルード */
#include "CTerrainLoader.h"
#include "direct3d.h"
#include <fstream>
#include <sstream>

// CTerrainLoaderクラスのstaticメンバ変数の初期化
CTerrainLoader* CTerrainLoader::instance = nullptr;

// コンストラクタ
CTerrainLoader::CTerrainLoader()
{
	// ファイルの数だけループ
	for (int i = 0; i < file_name.size(); i++)
	{
		// パスを完成させ、path配列に格納
		path.push_back(file_name[i].insert(0, "./stageTerrain_data/"));
	}
}

// デストラクタ
CTerrainLoader::~CTerrainLoader()
{
}

// 唯一のインスタンスを返す関数
CTerrainLoader* CTerrainLoader::GetInstance()
{
	// シングルトンが存在していないなら生成する
	if (!instance)
	{
		// シングルトンの生成
		instance = new CTerrainLoader();
		//コールバックとして登録
		std::atexit(CleanupSingleton);
	}
	//唯一のインスタンスを返す
	return instance;
}

// シングルトンの解放処理
void CTerrainLoader::CleanupSingleton()
{
	//インスタンスがあるなら解放する
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

// 地形データの読み込み
void CTerrainLoader::LoadTerrainData(TERRAIN_ID stage)
{
	// 前に読み込まれた情報をクリアする
	map_info.clear();

	// 読み込んだデータを格納
	std::string read_buf;

	// 指定されたcsvファイルを開く
	std::ifstream ifs_csv_file(path[(int)stage]);

	// ファイルが正常に開けているかチェック
	if (!ifs_csv_file.is_open())
	{
		MessageBoxA(NULL, "指定されたファイルが見つかりません", "エラー", MB_OK | MB_ICONERROR);
		return;
	}

	// ヘッダー行を読み飛ばす
	std::string header;
	getline(ifs_csv_file, header);

	// データを読み込む
	for (int i = 0 ;getline(ifs_csv_file, read_buf); i++)
	{
		// 「,」区切りごとにデータを読み込むためにistringstream型にする
		std::istringstream i_stream(read_buf);
		// マップ情報の配列の列(縦)をリサイズする
		map_info.resize(map_info.size() + 1);
		// 行に ','が現れるまで繰り返す
		for (int j = 0 ; getline(i_stream, read_buf, ','); j++)
		{
			// 読み込んだデータを整数に変換して行(横)の末尾に保存
			map_info[i].push_back(std::stoi(read_buf));
		}
	}

	// ファイルを閉じる
	ifs_csv_file.close();
}

// 読み込んだ地形データを取得を行う
std::vector<std::vector<int>> CTerrainLoader::GetTerrainData()
{
	if (map_info.empty())
	{
		MessageBoxA(NULL, "地形データが読み込まれていないか、csvファイル内にデータがありません", "エラー", MB_OK | MB_ICONERROR);
	}
	return map_info;
}

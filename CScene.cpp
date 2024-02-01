#include "CScene.h"
#include "ResultScene.h"

// staticメンバ変数を定義
std::vector<std::vector<int>> CScene::map_data;
std::list<CGameObject*> CScene::map_object;
ID3D11Buffer* CScene::vertexBufferMap;

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::CreateStage(TERRAIN_ID _id, CCamera* _useCamera)
{
	// マップデータのcsvファイルの読み込み
	CTerrainLoader::GetInstance()->LoadTerrainData(_id);
	map_data = CTerrainLoader::GetInstance()->GetTerrainData();
	
	// 画面左上を原点とした、始めのタイルの位置を設定
	float x_tile = ORIGIN_TILE_POS_X;
	float y_tile = ORIGIN_TILE_POS_Y;

	// 縦方向ループ
	for (int i = 0; i < map_data.size(); i++)
	{
		// y方向のタイルを置く位置を決定
		y_tile = ORIGIN_TILE_POS_Y - (TILE_HEIGHT * i);
		// 横方向ループ
		for (int j = 0; j < map_data[i].size(); j++)
		{
			// x方向のタイルを置く位置を決定
			x_tile = ORIGIN_TILE_POS_X + (TILE_WIDTH * j);

			// 読み込まれたデータが1ならマップタイルをつくる
			if (map_data[i][j] == 1)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO)));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT};
			}

			//	風が起きるオブジェクト生成（右方向）
			if (map_data[i][j] == 2)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WINDRIGHT_POS),{ 1.0f, 1.0f }, OBJECT_TYPE::WIND_RIGHT));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}

			//	風が起きるオブジェクト生成（上向き）
			if (map_data[i][j] == 3)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WINDRIGHT_POS), { 1.0f, 1.0f }, OBJECT_TYPE::WIND_UP));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			if (map_data[i][j] == 4)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CGameObject (vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TILE), { 1.0f, 1.0f }, OBJECT_TYPE::DAMEGE_TILE));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
		}
		// 次の行へ移動するのでx方向を元に戻す
		x_tile = ORIGIN_TILE_POS_X;
	}
}

void CScene::DestroyStage()
{
	// map_dataが解放済みでないなら解放処理を行う
	if (!map_data.empty())
	{
		// リストに登録されたオブジェクトの解放
		for (auto it = map_object.begin(); it != map_object.end(); it++)
		{
			delete(*it);
		}
		// オブジェクトのリストをクリアする
		map_object.clear();
	}

	// マップ用頂点バッファの解放
	SAFE_RELEASE(vertexBufferMap);
}

void CScene::DrawTerrain()
{
	// 地形オブジェクトの描画
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		(*it)->Draw();
	}
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

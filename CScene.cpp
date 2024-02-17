#include "CScene.h"

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
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::BLOCK)));
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
			// スケルトンタイル
			if (map_data[i][j] == 50)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CGameObject(vertexBufferMap, NULL, {1.0f, 1.0f}, OBJECT_TYPE::SKELETON_TILE));
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
			// 通常普通のタイル(模様無し)
			if (map_data[i][j] == 11)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::NOMAL_TILE)));
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
			// 黒いタイル
			if (map_data[i][j] == 12)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::darkTile)));
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
			// 敵
			if (map_data[i][j] == 66)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CEnemy(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY), { 0.333333f ,0.5f }, OBJECT_TYPE::ENEMY));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				map_object.back()->transform.position.z = -0.1f;
				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	風が起きるオブジェクト生成（右方向）
			if (map_data[i][j] == 2)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_RIGHT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_RIGHT));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_RIGHT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;

				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	右向き扇風機
			if (map_data[i][j] == 22)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::Senpuuki), { 0.5f ,0.333333f }, OBJECT_TYPE::WIND_RIGHT));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 2, 3, ANIM_PATTERN::WIND_RIGHT, 0.3f);

				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	風が起きるオブジェクト生成（右方向）(空中）
			if (map_data[i][j] == 30)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_RIGHT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_RIGHTS));
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

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_RIGHT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;
			}

			//	風が起きるオブジェクト生成（上向き）
			if (map_data[i][j] == 3)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_UP), { 1.0f, 0.2f }, OBJECT_TYPE::WIND_UP));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 1, 5, ANIM_PATTERN::WIND_ANIM_UP_LEFT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;

				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// 上向き扇風機
			if (map_data[i][j] == 33)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::Senpuuki), { 0.5f ,0.3333333f }, OBJECT_TYPE::WIND_UP));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 2, 3, ANIM_PATTERN::WIND_UP, 0.3f);

				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}

			// ダメージタイル
			if (map_data[i][j] == 4)
			{
				// マップタイルを1つnewする
				map_object.push_back(new Cdamagetile(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::DTILEX), { 1.0f, 1.0f }, OBJECT_TYPE::DAMAGE_TILE));
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
			if (map_data[i][j] == 25)	//下向きの画鋲
			{
				// マップタイルを1つnewする
				map_object.push_back(new Cdamagetile(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::DTILE_DOWN), { 1.0f, 1.0f }, OBJECT_TYPE::DAMAGE_DOWN));
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
			if (map_data[i][j] == 20)
			{
				// マップタイルを1つnewする
				map_object.push_back(new Cdamagetile(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TILE), { 1.0f, 1.0f }, OBJECT_TYPE::DAMAGE_TILEY));
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
			//	風が起きるオブジェクト生成（左方向）
			if (map_data[i][j] == 9)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_LEFT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_LEFT));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_UP_LEFT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;

				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// 左向き扇風機
			if (map_data[i][j] == 80)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::Senpuuki), { 0.5f ,0.333333f }, OBJECT_TYPE::WIND_LEFT));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 2, 3, ANIM_PATTERN::WIND_LEFT, 0.3f);

				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}

			if (map_data[i][j] == 40)
			{
				// マップタイルを1つnewする
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_LEFT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_LEFTS));
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

				//	アニメーション初期化
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_UP_LEFT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;
			}
			// ゴール
			if (map_data[i][j] == 99)
			{
				// ※ゴールだけ大きさを変更しています
				// マップタイルを1つnewする
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::HATA), { 1.0f, 1.0f }, OBJECT_TYPE::GOAL));
				// 使うカメラを設定
				map_object.back()->SetUseingCamera(_useCamera);
				// タイルのサイズをセットする
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH * 1.5;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT * 2.5;
				// タイルの位置をセットする
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile + 0.11f;
				// コライダーの設定
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT * 2};
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
		// 透明タイルは描画しない
		// 敵は後で描画する
		if ((*it)->GetObjectType() != OBJECT_TYPE::SKELETON_TILE &&
			(*it)->GetObjectType() != OBJECT_TYPE::ENEMY)
		{
			(*it)->Draw();
		}
	}
	// 敵の描画
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		if ((*it)->GetObjectType() == OBJECT_TYPE::ENEMY)
		{
			(*it)->Draw();
		}
	}
}

void CScene::UpdateTerrain()
{
	// 地形オブジェクトの描画
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		(*it)->Update();
	}
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

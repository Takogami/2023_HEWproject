#include "CScene.h"

std::vector<std::vector<int>> CScene::map_data;
std::list<CGameObject*> map_object;

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::CreateStage(TERRAIN_ID id)
{
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
			x_tile = ORIGIN_TILE_POS_X + (TILE_WIDTH * i);
		}

		// 次の行へ移動するのでx方向を元に戻す
		x_tile = ORIGIN_TILE_POS_X;
	}
}

void CScene::DestroyStage()
{
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

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
				map_object.push_back( new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO)) );
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

void CScene::CorrectPosition(CPlayer* moveObject, CGameObject* holdObject)
{
	float overlapX = moveObject->Bcol.sizeX / 2 + holdObject->Bcol.sizeX / 2 - std::abs(moveObject->Bcol.centerX - holdObject->Bcol.centerX);
	float overlapY = moveObject->Bcol.sizeY / 2 + holdObject->Bcol.sizeY / 2 - std::abs(moveObject->Bcol.centerY - holdObject->Bcol.centerY);

	if (overlapX < overlapY)
	{
		// X軸方向にめり込んでいる場合
		if (moveObject->Bcol.centerX < holdObject->Bcol.centerX)
		{
			moveObject->Bcol.centerX -= overlapX;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.x = moveObject->Bcol.centerX;
		}
		else
		{
			moveObject->Bcol.centerX += overlapX;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.x = moveObject->Bcol.centerX;
		}
	}
	else{
		// Y軸方向にめり込んでいる場合
		if (moveObject->Bcol.centerY < holdObject->Bcol.centerY)
		{
			moveObject->Bcol.centerY -= overlapY;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.y = moveObject->Bcol.centerY;
		}
		else
		{
			moveObject->Bcol.centerY += overlapY;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.y = moveObject->Bcol.centerY;
		}

		//コライダーの中心点とオブジェクトの中心点を連動させる
		moveObject->transform.position.x = moveObject->Bcol.centerX;
		moveObject->transform.position.y = moveObject->Bcol.centerY;
	}
}

bool CScene::TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2)
{
	// 中心点間の距離
	float distanceX = std::abs(obj1.centerX - obj2.centerX);
	float distanceY = std::abs(obj1.centerY - obj2.centerY);

	// 中心点間の距離がそれぞれの矩形の幅と高さの半分を足したものより小さい場合、重なっていると判定
	if (distanceX < (obj1.sizeX / 2 + obj2.sizeX / 2) && distanceY < (obj1.sizeY / 2 + obj2.sizeY / 2))
	{
		return true;
	}

	return false;
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

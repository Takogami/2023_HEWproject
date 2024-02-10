#include "CEnemy.h"
#include "CScene.h"
#include "CWind.h"

void CEnemy::EnemyPattern()
{
	switch (State)
	{
	case EState::NORMAL:
		SetState(EState::LEFTWALK);
		walkTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
		walkTime->StartTimer();
		break;
	case EState::LEFTWALK:
		dir.x = -1.0f;
		prevFrameDir.x = dir.x;
		if (walkTime->GetTimerState() == TIMER_STATE::END)//(prevFrameCorrect.x >= 1)
		{
			SetState(EState::RIGHTWALK);
			walkTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
			walkTime->StartTimer();
		}
		break;
	case EState::RIGHTWALK:
		dir.x = 1.0f;
		prevFrameDir.x = dir.x;
		if (walkTime->GetTimerState() == TIMER_STATE::END)//(prevFrameCorrect.x <= -1)
		{
			SetState(EState::LEFTWALK);
			walkTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
			walkTime->StartTimer();
		}
		break;
	default:
		break;
	}
}

CEnemy::CEnemy(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// 初期スピード設定
	SetMoveSpeed(0.005f);
	// 重力を初期値とする
	velocity.y = gravity;
	walkTime = new CTimer;
}

EState CEnemy::GetState()
{
	return State;
}

void CEnemy::SetState(EState state)
{
	State = state;
}

void CEnemy::Update()
{
	// 風の影響を受けていないなら向きを戻す
	if (dir_wind.x == 0.0f)
	{
		// 向きを戻す
		dir.x = 0.0f;
	}
	if (dir_wind.y == 0.0f)
	{
		// 向きを戻す
		dir.y = -1.0f;
	}

	EnemyPattern();

	// タイマーの更新
	walkTime->Update();

	// 前フレームの補正方向を初期化
	prevFrameCorrect = { 0 };

	// 単位ベクトル化(矢印を１にする) = 正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);					// 正規化する
	DirectX::XMStoreFloat3(&dir, v);					// 元の変数dirに戻す

	// 風の影響でのy方向の速度が限界値を超えないようにする
	if ((dir_wind.y == 1.0f || dir_wind.y == -1.0f) && velocity.y > velocityY_limit)
	{
		velocity.y = velocityY_limit;
	}

	velocity.y += gravity;

	// ベクトルに速度をかけて位置を変更
	this->transform.position.x += dir.x * velocity.x;
	this->transform.position.y += dir.y * velocity.y;

	// 移動量に風の計算を加える
	if (dir_wind.x == 1.0f)
	{
		windStrength -= 0.001f;
		if (windStrength <= 0.0f)
		{
			dir_wind.x = 0.0f;
			windStrength = 0.0f;
		}
		this->transform.position.x += windStrength;
	}
	// 
	if (dir_wind.y == 1.0f)
	{
		windStrength -= 0.001f;
		if (windStrength <= 0.0f)
		{
			dir_wind.y = 0.0f;
			windStrength = 0.0f;
		}
		this->transform.position.y += windStrength;
	}


	// 親クラスのUpdate()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の更新処理を行う
	CGameObject::Update();

	// 地形との当たり判定と補正
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		if (CCollision::TestBoxCollision(this->Bcol, (*it)->Bcol))
		{
			switch ((*it)->GetObjectType())
			{
			case OBJECT_TYPE::NORMAL:
				// コライダーの位置を補正し、補正した方向を受け取る
				CORRECT_DIR test = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
				prevFrameCorrect.x += test.x;
				prevFrameCorrect.y += test.y;


				// 天井にぶつかっていたならジャンプ力を0にする
				if (prevFrameCorrect.y == -1)
				{
					dir.y = -1.0f;		// 向きを下にする
				}
				// 重力によって地面に衝突していたなら
				if (prevFrameCorrect.y == 1)
				{
					dir.y = -1.0f;
					velocity.y = 0.0f;				// 速度Yを0に戻す
					velocity.y -= gravity;				// 速度Yを0に戻す
				}

				// オブジェクトの位置とコライダーの中心を合わせる
				this->transform.position.x = this->Bcol.centerX;
				this->transform.position.y = this->Bcol.centerY;
				break;

			case OBJECT_TYPE::WIND_RIGHT:	//	風（右向き）
				dir_wind.x = 1.0f;
				dir.x = 1.0f;
				windStrength = 0.01f;
				// オブジェクトの位置とコライダーの中心を合わせる
				this->Bcol.centerX = this->transform.position.x;
				this->Bcol.centerY = this->transform.position.y;
				break;

			case OBJECT_TYPE::WIND_UP:		//	風（上向き）
				dir_wind.y = 1.0f;
				dir.y = 1.0f;
				windStrength = 0.01f;
				break;

			default:
				break;
			}
		}
	}
}

void CEnemy::Draw()
{
	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();
}

CEnemy::~CEnemy()
{
	delete walkTime;
	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}

#include "CPlayer.h"
#include "CScene.h"
#include "CWind.h"

// コントローラーを使う場合はtrueを指定
#define USE_CONTROLLER (false)

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// 初期スピード設定
	SetMoveSpeed(0.05f);
	// 重力を初期値とする
	velocity.y = gravity;
}

void CPlayer::PlayerInput()
{
#if USE_CONTROLLER == true

	// スティック入力一時保存用
	float input_stickX;
	float input_stickY;

	// スティックの入力を保存
	input_stickX = gInput->GetLeftStickX();

	// 前のフレームでめり込んだ方向でないなら移動量を適応する
	if ((input_stickX > 0.0f && prevFrameCorrect.x != -1) ||
		(input_stickX < 0.0f && prevFrameCorrect.x != 1))
	{
		dir.x = input_stickX;
	}
	// 前のフレームでめり込んだ方向に移動しようとしてるなら移動量を適応しない
	else
	{
		dir.x = 0;
	}
	// Bボタン入力でとりあえずのジャンプ操作
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A))
	{
		isJump = true;
	/*	this->transform.position.y = -0.2f;*/
	}

#else
	switch (State)
	{
	case PState::NORMAL:
		if (gInput->GetKeyPress(VK_DOWN) /*&& prevFrameCorrect.y != 1*/)
		{
			if (!gInput->GetKeyPress(VK_UP))
			{
				/*dir.y = -1.0f;
				prevFrameDir.y = dir.y;*/

				SetState(PState::FALL);
				transform.scale.y *= 0.1f;
				this->Bcol.sizeY *= 0.1f;
				transform.position.y -= 0.1f;
			}
			else
			{
				/*dir.y = prevFrameDir.y;*/
			}
		}
		else if (gInput->GetKeyPress(VK_UP) && prevFrameCorrect.y != -1)
		{
			if (!gInput->GetKeyPress(VK_DOWN))
			{
				//dir.y = 1.0f;
				prevFrameDir.y = dir.y;
			}
			else
			{
				dir.y = prevFrameDir.y;
			}
		}
		if (gInput->GetKeyPress(VK_LEFT) && prevFrameCorrect.x != 1)
		{
			if (!gInput->GetKeyPress(VK_RIGHT))
			{
				dir.x = -1.0f;
				prevFrameDir.x = dir.x;
			}
			else
			{
				dir.x = prevFrameDir.x;
			}
		}
		else if (gInput->GetKeyPress(VK_RIGHT) && prevFrameCorrect.x != -1)
		{
			dir.y = prevFrameDir.y;
			if (!gInput->GetKeyPress(VK_LEFT))
			{
				dir.x = 1.0f;
				prevFrameDir.x = dir.x;
			}
			else
			{
				dir.x = prevFrameDir.x;
			}
		}
		if (gInput->GetKeyPress(VK_TAB))
		{
			isJump = true;
		}
		if (prevFrameCorrect.x != 0)
		{

			SetState(PState::FALL);
			transform.scale.y *= 0.1f;
			this->Bcol.sizeY *= 0.1f;
			transform.position.y -= 0.1f;
		}
		break;

	case PState::FALL:
		if (gInput->GetKeyPress(VK_UP))
		{
			if (!gInput->GetKeyPress(VK_DOWN))
			{
				SetState(PState::NORMAL);
				transform.scale.y *= 10.0;
				this->Bcol.sizeY *= 10.0f;
				transform.position.y += 0.1f;
			}
			else
			{

			}
			if (gInput->GetKeyTrigger(VK_LEFT))
			{
				if (!gInput->GetKeyTrigger(VK_RIGHT))
				{
					SetState(PState::BREAKLEFT);
				}
				else
				{

				}
			}
			else if (gInput->GetKeyTrigger(VK_RIGHT))
			{
				if (!gInput->GetKeyTrigger(VK_LEFT))
				{
					SetState(PState::BREAKRIGHT);
				}
				else
				{

				}
			}
			if (gInput->GetKeyPress(VK_TAB))
			{
				isJump = true;
			}
		}
			break;

	case PState::BREAKLEFT:
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			if (!gInput->GetKeyTrigger(VK_LEFT))
			{
				SetState(PState::FALL);
			}
			else
			{

			}
		}
		break;

	case PState::BREAKRIGHT:
		if (gInput->GetKeyTrigger(VK_LEFT))
		{
			if (!gInput->GetKeyTrigger(VK_RIGHT))
			{
				SetState(PState::FALL);
			}
			else
			{

			}
		}
		break;

	default:
		break;
	}
#endif

}

float CPlayer::Jump()
{
	// 向きを上にする
	dir.y = 1.0f;
	// ジャンプ力を重力に従って更新
	jumpStrength -= gravity;
	// 計算したジャンプ力を適応
	return jumpStrength;
}

void CPlayer::Update()
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

	// プレイヤー操作関連の入力処理
	PlayerInput();

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

	// 重力の影響を受けてY軸方向の速度を更新
	// ジャンプ中ならジャンプ力の更新処理を行う
	velocity.y = isJump ? Jump() : velocity.y += gravity;

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
				prevFrameCorrect = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);

				// 天井にぶつかっていたならジャンプ力を0にする
				if (prevFrameCorrect.y == -1)
				{
					dir.y = -1.0f;		// 向きを下にする
					jumpStrength = 0;	// ジャンプ力を0にする
				}
				// 重力によって地面に衝突していたなら
				if (prevFrameCorrect.y == 1)
				{
					dir.y = -1.0f;
					velocity.y = 0.0f;				// 速度Yを0に戻す
					jumpStrength = ini_jumpStrength;
					isJump = false;
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

PState CPlayer::GetState()
{
	return State;
}

void CPlayer::SetState(PState state)
{
	State = state;
}

void CPlayer::Draw()
{
	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();
}

CPlayer::~CPlayer()
{
	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}

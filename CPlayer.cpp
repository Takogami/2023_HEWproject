#include "CPlayer.h"
#include "CScene.h"

// コントローラーを使う場合はtrueを指定
#define USE_CONTROLLER (true)

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv) : CGameObject(vb, tex, uv)
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
	}

#else

	if (gInput->GetKeyPress(VK_DOWN) && prevFrameCorrect.y != 1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->GetKeyPress(VK_UP))
		{
			// 押されていないなら方向を更新する
			dir.y = -1.0f;
			prevFrameDir.y = dir.y;
		}
		else
		{
			// 押されてしまっているなら前の方向をそのまま適応
			dir.y = prevFrameDir.y;
		}
	}
	else if (gInput->GetKeyPress(VK_UP) && prevFrameCorrect.y != -1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->GetKeyPress(VK_DOWN))
		{
			// 押されていないなら方向を更新する
			dir.y = 1.0f;
			prevFrameDir.y = dir.y;
		}
		else
		{
			// 押されてしまっているなら前の方向をそのまま適応
			dir.y = prevFrameDir.y;
		}
	}

	if (gInput->GetKeyPress(VK_LEFT) && prevFrameCorrect.x != 1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->GetKeyPress(VK_RIGHT))
		{
			// 押されていないなら方向を更新する
			dir.x = -1.0f;
			prevFrameDir.x = dir.x;
		}
		else
		{
			// 押されてしまっているなら前の方向をそのまま適応
			dir.x = prevFrameDir.x;
		}
	}
	else if (gInput->GetKeyPress(VK_RIGHT) && prevFrameCorrect.x != -1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->GetKeyPress(VK_LEFT))
		{
			// 押されていないなら方向を更新する
			dir.x = 1.0f;
			prevFrameDir.x = dir.x;
		}
		else
		{
			// 押されてしまっているなら前の方向をそのまま適応
			dir.x = prevFrameDir.x;
		}
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
	// 向きを戻す
	dir.x = 0.0f;
	dir.y = 0.0f;

	// プレイヤー操作関連の入力処理
	PlayerInput();

	// 前フレームの補正方向を初期化
	prevFrameCorrect = { 0 };

	// 単位ベクトル化(矢印を１にする) = 正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);					// 正規化する
	DirectX::XMStoreFloat3(&dir, v);					// 元の変数dirに戻す
	
	// 重力の影響を受けてY軸方向の速度を更新
	// ジャンプ中ならジャンプ力の更新処理を行う
	velocity.y = isJump ? Jump() : velocity.y -= gravity;

	// ベクトルに速度をかけて位置を変更
	this->transform.position.x += dir.x * velocity.x;
	this->transform.position.y += velocity.y;

	// 親クラスのUpdate()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の更新処理を行う
	CGameObject::Update();

	// 地形との当たり判定と補正
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		if (CCollision::TestBoxCollision(this->Bcol, (*it)->Bcol))
		{
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
		}
	}
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

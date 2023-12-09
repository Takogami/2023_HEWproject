#include "CPlayer.h"
#include "CInput.h"
#include "CScene.h"

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv) : CGameObject(vb, tex, uv)
{
	// 初期スピード設定
	SetMoveSpeed(0.05f);
}

void CPlayer::Input()
{
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyPress(VK_DOWN) && prevFrameCorrect.y != 1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_UP) && !gInput->GetKeyPress(VK_UP))
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
	else if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyPress(VK_UP)) && prevFrameCorrect.y != -1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) && !gInput->GetKeyPress(VK_DOWN))
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

	if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT) || gInput->GetKeyPress(VK_LEFT)) && prevFrameCorrect.x != 1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) && !gInput->GetKeyPress(VK_RIGHT))
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
	else if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || gInput->GetKeyPress(VK_RIGHT)) && prevFrameCorrect.x != -1)
	{
		// 同時に反対のキーが押されていないか
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT) && !gInput->GetKeyPress(VK_LEFT))
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

	// スティック入力一時保存用
	float input_stickX, input_stickY;

	// スティックの入力を保存
	input_stickX = gInput->GetRightStickX();
	input_stickY = gInput->GetRightStickY();

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
	// 前のフレームでめり込んだ方向でないなら方向を適応
	if ((input_stickY > 0.0f && prevFrameCorrect.y != -1) ||
		(input_stickY < 0.0f && prevFrameCorrect.y != 1))
	{
		dir.y = input_stickY;
	}
	else
	{
		dir.y = 0;
	}
}

void CPlayer::Update()
{
	// 向きを戻す
	dir.x = 0.0f;
	dir.y = 0.0f;

	Input();

	// 前フレームの補正方向を初期化
	prevFrameCorrect = { 0 };

	// 単位ベクトル化(矢印を１にする) = 正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);					// 正規化する
	DirectX::XMStoreFloat3(&dir, v);					// 元の変数dirに戻す

	// ベクトルに速度をかけて位置を変更
	this->transform.position.x += dir.x * moveSpeed;
	this->transform.position.y += dir.y * moveSpeed;

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

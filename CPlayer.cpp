#include "CPlayer.h"
#include "CInput.h"
#include "CScene.h"

//明示的に親クラスのコンストラクタを呼び出す
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv) : CGameObject(vb, tex, uv)
{
}

void CPlayer::Update()
{
	// 向きを戻す
	dir.x = 0.0f;
	dir.y = 0.0f;

	// 移動入力
	if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyPress(VK_DOWN)))
	{
		dir.y = -1.0f;
	}
	else if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyPress(VK_UP))
	{
		dir.y = 1.0f;
	}
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT) || gInput->GetKeyPress(VK_LEFT))
	{
		dir.x = -1.0f;
	}
	else if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || gInput->GetKeyPress(VK_RIGHT))
	{
		dir.x = 1.0f;
	}

	//単位ベクトル化(矢印を１にする) = 正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);					// 正規化する
	DirectX::XMStoreFloat3(&dir, v);					// 元の変数dirに戻す

	// ベクトルに速度をかけて位置を変更
	this->transform.position.x += dir.x * 0.03f;
	this->transform.position.y += dir.y * 0.03f;

	// 親クラスのUpdate()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の更新処理を行う
	CGameObject::Update();
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

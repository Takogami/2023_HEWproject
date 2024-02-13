#include "CCursor.h"
#include "CInput.h"
#include "CEase.h"

CCursor::CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// イージングの実体化
	curEase = new CEase;
}

void CCursor::CursorInput()
{
	// オブジェクトがアクティブでないなら更新は行わない
	if (!active)
	{
		return;
	}

	// 移動入力
	if ((gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyTrigger(VK_DOWN)))
	{
		scene_count++;// 下に1つ進める
	}
	else if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyTrigger(VK_UP))
	{
		scene_count += sceneNum - 1;// 上に1つ進める
	}

	// タイトルの選択項目数を超過した場合に数を合わせる
	// (scene_countが0～SCENE_COUNT-1の間になるように調整)
	scene_count %= sceneNum;

	// カーソルの位置決め
	this->transform.position.y = ini_position.y - moveDistance * scene_count;
}

void CCursor::Update()
{
	// オブジェクトがアクティブでないなら更新は行わない
	if (!active)
	{
		return;
	}

	// イージングの処理
	curEase->Update();
	if (curEase->GetState() == STATE::END)
	{
		// 折り返しである時
		if (!curReturn)
		{
			curEase->Init(&transform.position.x, transform.position.x - 0.02f, 0.5f, 0, EASE::easeOutExpo);
			// 折り返しフラグを上げる
			curReturn = true;
		}
		else
		{
			curEase->Init(&transform.position.x, transform.position.x + 0.02f, 0.5f, 0, EASE::easeInExpo);
			// 折り返しフラグを下げる
			curReturn = false;
		}
	}

	CGameObject::Update();
}

void CCursor::Draw()
{
	// オブジェクトがアクティブでないなら更新は行わない
	if (!active)
	{
		return;
	}

	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();
}

void CCursor::Init(FLOAT_XY ini_pos, int scene, float move)
{
	// 遷移できるシーン数を設定
	sceneNum = scene;
	// 初期位置と移動量を設定
	ini_position = ini_pos;
	moveDistance = move;
	// 初期位置を代入しておく
	transform.position.x = ini_position.x;
	transform.position.y = ini_position.y;
	// イージングの初期化
	curEase->Init(&transform.position.x, transform.position.x + 0.02f, 0.5f, 0, EASE::easeInExpo);
}

//CCursorでの列挙型のSceneを取得する
CCursor_Point CCursor::GetCursorPoint() const
{
	if (!active)
	{
		return CCursor_Point::INACTIVE;
	}

	switch (scene_count)
	{
	case 0:
		return CCursor_Point::STAGE;
	case 1:
		return CCursor_Point::EXIT;
	case 2:
		return CCursor_Point::INACTIVE;
	default:
		// エラー処理やデフォルトの挙動を設定
		return CCursor_Point::INACTIVE; // 仮の値です。適切な処理に変更してください。
	}
}

CCursor::~CCursor()
{
	delete curEase;

	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}


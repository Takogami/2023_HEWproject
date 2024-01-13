#include "CCursor.h"
#include "CInput.h"

CCursor::CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex) : CGameObject(vb, tex, uv)
{

}

void CCursor::Update()
{
	// 移動入力
	if ((gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyTrigger(VK_DOWN)))
	{
		scene_count++;// 下に1つ進める
	}
	else if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyTrigger(VK_UP))
	{
		scene_count += SCENE_COUNT-1;// 上に1つ進める
	}

	// タイトルの選択項目数を超過した場合に数を合わせる
	// (scene_countが0～SCENE_COUNT-1の間になるように調整)
	scene_count %= SCENE_COUNT;

	// カーソルの位置決め
	switch (scene_count)
	{
	case 0://ステージ選択時
		this->transform.position.y = -0.3f;// y=0.3 = ステージのカーソルのy座標
		break;
	case 1://オプション選択時
		this->transform.position.y = -0.6f;// y=0.6 = オプションのカーソルのy座標
		break;
	case 2://ゲーム終了選択時
		this->transform.position.y = -0.9f;// y=0.9 = ゲーム終了のカーソルのy座標
		break;
	}

	gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A);

	CGameObject::Update();
}

void CCursor::Draw()
{
	// 親クラスのDraw()を明示的に呼び出す
	// 全てのゲームオブジェクト共通の描画処理を行う
	CGameObject::Draw();
}

//CCursorでの列挙型のSceneを取得する
CCursor_Point CCursor::GetCursorPoint() const
{
	switch (scene_count)
	{
	case 0:
		return CCursor_Point::STAGE;
	case 1:
		return CCursor_Point::OPTION;
	case 2:
		return CCursor_Point::EXIT;
	default:
		// エラー処理やデフォルトの挙動を設定
		return CCursor_Point::STAGE; // 仮の値です。適切な処理に変更してください。
	}
}

CCursor::~CCursor()
{

	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}


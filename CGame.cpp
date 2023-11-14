#include "CGame.h"
#include "CInput.h"
#include <XInput.h>

//コンストラクタ
CGame::CGame()
{
	//CTextureLoaderのシングルトンを生成
	TexLoader = CTextureLoader::GetInstance();
	//テクスチャ読み込み
	TexLoader->LoadTexture();

	//カメラの作成
	Cam = new CCamera;

	//プレイヤーの実体化と初期化
	player = new CGameObject(vertexBufferCharacter, TexLoader->GetTex(TEX_ID::CHAR1),{0.33f ,0.25f});
	//自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	//プレイヤーの実体化と初期化
	player2 = new CGameObject(vertexBufferCharacter, TexLoader->GetTex(TEX_ID::TAKO));
	//自身の投影にカメラを使用しない
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.5f;
	player2->transform.position = { -0.5f, -0.5f };

	//乱数の初期化(注意：srand関数呼び出しはアプリケーション開始時に1回だけ)
	srand(GetTickCount64());

	//初期シーン設定
	SetScene(TITLE);

	// CSceneManagerの初期化
	sceneManager = new CSceneManager();
}

void CGame::Update()
{
	// Aボタンが押されたかどうかをチェックしてシーンを切り替える
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_A)) {
		// TITLEとRESULTの間をトグル
		SetScene((scene == TITLE) ? RESULT : TITLE);
	}

	// 現在のシーンを更新
	sceneManager->Update();

	//シーンごとのUpdate関数を実行
	switch (scene)
	{
	case TITLE:
		UpdateTitle();
		break;
	case STAGE:
		break;
	case RESULT:
		break;
	}
}


void CGame::SetScene(SCENE_STATE nextScene)
{
	//画面遷移開始時
	if (newScene != nextScene)
	{
		newScene = nextScene;	//遷移先画面を保存
		fadeState = FADE_OUT;	//フェードアウトを開始
	}
	//フェードアウト終了で実際にシーンを切り替える
	else
	{
		scene = nextScene;	//画面の切り替え
		fadeState = FADE_IN;//切り替えたのでフェードインの開始

		//シーンごとのBGM再生
		switch (scene)
		{
		case CGame::TITLE:
			break;

		case CGame::STAGE:
			break;

		case CGame::RESULT:
			break;
		}
	}
}

CGame::~CGame()
{
	//テクスチャのアンロード
	TexLoader->UnloadTexture();

	delete player;
	delete player2;
	delete Cam;

	SAFE_RELEASE(vertexBufferCharacter);

	// CSceneManagerの解放
	delete sceneManager;
}

void CGame::UpdateTitle()
{
	//画面塗りつぶしと設定
	D3D_ClearScreen();

	//以下とりあえずカメラ移動のテスト用
	static float camPos_x = 0.0f;
	static float camPos_y = 0.0f;
	camPos_x += 0.001f;
	camPos_y += 0.001f;
	Cam->SetCameraPosition(camPos_x, camPos_y);

	//カメラの更新
	Cam->Update();

	//プレイヤー１の更新
	player->Update();
	player->Draw();

	//プレイヤー２の更新(カメラ不使用)
	player2->Update();
	player2->Draw();

	//画面更新
	D3D_UpdateScreen();
}

//検証用
void CGame::UpdateResult()
{
	//画面塗りつぶしと設定
	D3D_ClearScreen();

	//以下とりあえずカメラ移動のテスト用
	static float camPos_x = 0.0f;
	static float camPos_y = 0.0f;
	camPos_x += 0.001f;
	camPos_y += 0.001f;
	Cam->SetCameraPosition(camPos_x, camPos_y);

	//カメラの更新
	Cam->Update();

	//プレイヤー１の更新
	player->Update();
	player->Draw();

	

	//画面更新
	D3D_UpdateScreen();
}


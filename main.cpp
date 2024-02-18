#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う

#include <Windows.h>
#include <Windowsx.h>
#include "direct3d.h"
#include "CGame.h"
#include "CInput.h"

// マクロ定義
#define CLASS_NAME    "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME   "かみぺったん"// ウィンドウの名前

// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//グローバル変数の宣言
CGame* gGame;
CInput* gInput = new CInput;

//エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	/* ウインドウのパラメータ（スタイルなど）を決めて、Windowsに登録 */

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;								//アイコンの変更
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		//カーソル変更
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;							//ウインドウのメニュー設定
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	/* ウインドウを作る関数を呼び出す */

	// 画面サイズを取得
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd; // ウインドウハンドル = ウインドウID
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_POPUP,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標
		screenX,// ウィンドウの幅
		screenY,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	/* ウインドウを表示する関数を呼び出す */

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	//ゲームループに入る前にDirectXの初期化をする
	D3D_Create(hWnd);

	//ゲームの初期化
	gGame = new CGame();

	/* アプリが終わらないように永久ループを作る
	→ループの中でユーザーの操作を待ち構える */
	MSG msg;

	char str[100];

	//fps表示用
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();	//開始時間を保存
	long long nowTick = oldTick;			//現在時間を取得

	//fps固定用変数
	LARGE_INTEGER liWork;	//関数から値を受け取る用
	long long frequency;	//計測精度

	//計測精度を取得
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;	//１秒当たりの解像度が入る
	//1フレームあたりのカウント値を計算
	long long numCount_1flame = frequency / 60;	//60fpsで計算
	//現在時間(単位：カウント)を取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	//メッセージループ(ゲームループ)
	while (true) {
		//ユーザー操作(イベント)が起こったか調べる
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage)
		{
			//イベントが起こったのでコールバックを呼び出す
			DispatchMessage(&msg);

			//アプリを終了させるメッセージが来たら永久ループから抜ける(breakで抜ける)
			if (msg.message == WM_QUIT) {
				break;
			
			}
		}
		//何もメッセージがないとき
		else {

			//1/60秒経過したか？
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart;	//現在時間を取得(単位：カウント)

			if (nowCount >= oldCount + numCount_1flame) {
				//ゲームの処理
				gGame->Update();
				gInput->Update();
				fpsCounter++;	//ゲームループ実行関数を＋１
				oldCount = nowCount;
			}

			nowTick = GetTickCount64();

			//1秒経過したか？
			//+1000 … ミリ秒単位であるため
			if (nowTick >= oldTick + 1000) {

				//fpsを表示する
				wsprintfA(str, "かみぺったん    FPS : %d", fpsCounter);
				SetWindowTextA(hWnd, str);
				//カウンターをリセット
				fpsCounter = 0;
				oldTick = nowTick;
			}

		}
	}	//end gameloop

	delete gGame;
	delete gInput;

	//DirectXの解放処理
	D3D_Release();

	// ループを抜けたらアプリの終了処理をする
	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;

	case WM_KEYDOWN:
		gInput->SetKeyDownState(wParam);
		break;

	case WM_KEYUP:
		gInput->SetKeyUpState(wParam);
		break;

	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
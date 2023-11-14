#pragma once

//キー入力を判定するクラス
//仕組み：WndProc関数でキーが押された/離されたイベント時にそれを記録していく。
//        キーの状態を判定する関数が呼ばれたら、その状態を返す。
#include <Windows.h>  // WORD型が含まれているヘッダーファイル
class CInput
{
	//メンバ変数
	

	//キー状態の記録領域
	bool keyState[256] = { false };
	//１フレーム前のキー入力状態の記憶領域
	bool oldKeyState[256] = { false };

public:
	//メンバ関数

	//キーが押されたのを記録する関数
	void SetKeyDownState(int key);

	//キーが離されたのを記録する関数
	void SetKeyUpState(int key);

	//キープレスが発生しているか返す関数
	bool GetKeyPress(int key);

	//キートリガーが発生しているか返す関数
	bool GetKeyTrigger(int key);

	//ゲームループの最後でキー状態をoldKeyStateを更新する関数
	void Update();

	// Xboxコントローラーのボタンの状態を取得するメソッド
	bool IsControllerButtonPressed(WORD button);
};

//唯一の実体変数のextern宣言
extern CInput* gInput;


#pragma once

//キー入力を判定するクラス
//仕組み：WndProc関数でキーが押された/離されたイベント時にそれを記録していく。
//        キーの状態を判定する関数が呼ばれたら、その状態を返す。

/* インクルード */
#include <Windows.h>	// WORD型が含まれているヘッダーファイル
#include <XInput.h>		// コントローラーの入力関連のヘッダーファイル

//XInputライブラリのリンク設定
#pragma comment (lib,"XInput.lib")

class CInput
{
	//メンバ変数
	int Presstime = 0;

	XINPUT_STATE state;
	XINPUT_STATE oldState;  // 新しく追加

	//キー状態の記録領域
	bool keyState[256] = { false };
	//１フレーム前のキー入力状態の記憶領域
	bool oldKeyState[256] = { false };

	// 入力をロックするかのフラグ
	bool inputLock = false;

	// 振動パラメータ
	XINPUT_VIBRATION vibrationPalam;
	// バイブレーションが行われているかのフラグ
	bool vibrationFlg = false;
	// バイブレーションが始まって経過した時間
	int NowVibrationFlame = 0;
	// 振動させる時間(フレーム単位)
	int vibrationFlame = 0;

	//	デッドゾーンの閾値
	const float DEADZONE_THRESHOLD = 0.2f;

public:
	//メンバ関数
	CInput();  // コンストラクタを追加

	// 入力を受け付けるかどうかを設定
	void InputLock(bool lock);

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
	// Xboxコントローラーのボタンの状態を取得するメソッド
	bool IsControllerButtonTrigger(WORD button);
	// Xboxコントローラーのボタンの状態を取得するメソッド
	bool IsControllerButtonRepeat(WORD button, int cCount, int cTime);

	// コントローラーの左スティックのX軸の値を取得
	float GetLeftStickX();
	// コントローラーの左スティックのY軸の値を取得
	float GetLeftStickY();
	// コントローラーの右スティックのX軸の値を取得
	float GetRightStickX();
	// コントローラーの右スティックのY軸の値を取得
	float GetRightStickY();

	//	コントローラーの左スティックのX軸の値を取得する（デッドゾーン考慮）
	float GetLeftStickXWithDeadzone();
	//	コントローラーの左スティックのY軸の値を取得する（デッドゾーン考慮）
	float GetLeftStickYWithDeadzone();
	//	コントローラーの右スティックのX軸の値を取得する（デッドゾーン考慮）
	float GetRightStickXWithDeadzone();
	//	コントローラーの右スティックのY軸の値を取得する（デッドゾーン考慮）
	float GetRightStickYWithDeadzone();
	// コントローラーの振動
	// 引数1 : 振動させる時間(フレーム単位) 引数2 : 振動の強さ(0~65535まで)
	void ControllerVibration(int vibration, int vibStrength);
};

//唯一の実体変数のextern宣言
extern CInput* gInput;


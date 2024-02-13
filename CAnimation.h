#pragma once

#include <vector>
#include "direct3d.h"

// アニメーション終端
#define ANIM_LOOP	(-1)	// アニメーションをループ
#define ANIM_STOP	(-2)	// アニメーションをストップ
#define ANIM_FINISH	(-3)	// アニメーションを終了

// アニメーションパターン列挙型
enum class ANIM_PATTERN
{
	NO_ANIM = 0,
	TEST,

	LEFTWALK,	//左に歩く
	RIGHTWALK,	//右に歩く
	FALLDOWN,	//倒れる
	GETUP,		//起き上がる
	BREAKLEFT,	//左に折れる
	BREAKRIGHT,	//右に折れる
	FIXLEFT,	//左に起き上がる
	FIXRIGHT,	//右に起き上がる
	JAMP,		//ジャンプ
	FLAYING,	//飛んでる状態		
	FALL,		//倒れている状態

	BOOK,		//本の動き
	BOOK_REVERSE,
	ENEMY_MOVE,
	ENEMY_MOVE_R,
};

class CAnimation
{
public:
	// 更新
	void Update();
	// アニメーションのスピードを設定
	void SetAnimationSpeed(float sp);
	// アニメーションパターンの設定
	void SetAnimationPattern(ANIM_PATTERN pattern);
	// アニメーションパターンの設定
	void SetMovementUV(FLOAT_XY movement);
	// 横分割数の設定
	void SetSpritU(int sprit);
	// 縦分割数の設定
	void SetSpritV(int sprit);
	// アニメーションの再生
	void PlayAnimation();
	// アニメーションの停止
	void StopAnimation();
	// アニメーションの進行状況をリセット
	void ResetAnimation();
	// 遷移アニメーション中かを設定
	void SetIsAnimation(bool anim);
	// 遷移アニメーションの再生状態を取得
	bool GetIsAnimation();
	// 現在のuvを取得
	FLOAT_XY GetUV();

private:
	// アニメーションテーブル
	std::vector<std::vector<int>> animationTable
	{
		{ 0, ANIM_STOP },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ANIM_LOOP},

		{ 9, 8, 7, 6, 5, 6, 7, 8, ANIM_LOOP},	//左に歩く
		{ 0, 1, 2, 3, 4, 3, 2, 1, ANIM_LOOP},	//右に歩く
		{ 20, 21, 22, 23, 24, ANIM_STOP},	//倒れる
		{ 25, 26, 27, 28, 29, ANIM_STOP},	//起き上がる
		{ 10, 11, 12, 13, 14, ANIM_STOP},	//左に折れる
		{ 15, 16, 17, 18, 19, ANIM_STOP},	//右に折れる
		{ 14, 13, 12, 11, 10, ANIM_STOP},	//左に起き上がる
		{ 19, 18, 17, 16, 15, ANIM_STOP},	//右に起き上がる
		{ 42, 43, 44, 43, 42, 41, 40, ANIM_STOP},	//ジャンプ
		{ 45, 46, 47, 48, 49, 48, 47, 46, ANIM_LOOP},	//飛んでる状態
		{ 10, ANIM_STOP },	//倒れている状態

		{ 0, 1, 2, 3, 4, 0, ANIM_STOP},	//本の動き
		{ 0, 4, 3, 2, 1, 0, ANIM_STOP},	//本逆
		{ 0, 0, 0, 1, 2, 1, ANIM_LOOP},
		{ 5, 5, 5, 4, 3, 4, ANIM_LOOP},

	};

	// アニメーションスピード
	float animationSpeed = 0.0f;
	// アニメーションパターン
	ANIM_PATTERN anim_pattern = ANIM_PATTERN::NO_ANIM;
	// 現在のuv座標
	FLOAT_XY uv = { 0.0f, 0.0f };
	// uv移動量
	FLOAT_XY uv_movement = { 0.0f, 0.0f };
	// アニメーション進行カウンター
	float animCounter = 0;
	// 横分割数
	int spritU = 1;
	// 縦分割数
	int spritV = 1;
	// 再生中フラグ
	bool playing = true;
	//遷移アニメーションフラグ
	bool isanim = false;
};


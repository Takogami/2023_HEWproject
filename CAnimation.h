#pragma once

#include <vector>
#include "direct3d.h"

// アニメーション終端
#define ANIM_LOOP	(-1)	// アニメーションをループ
#define ANIM_STOP	(-2)	// アニメーションをストップ

// アニメーションパターン列挙型
enum class ANIM_PATTERN
{
	NO_ANIM = 0,
	TEST,
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
	// アニメーションの再生
	void PlayAnimation();
	// アニメーションの停止
	void StopAnimation();
	// アニメーションの進行状況をリセット
	void ResetAnimation();
	// 現在のuvを取得
	FLOAT_XY GetUV();

private:
	// アニメーションテーブル
	std::vector<std::vector<int>> animationTable
	{
		{ 0, ANIM_LOOP },
		{ 6, 7, 8, 7, ANIM_LOOP},
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
	// 再生中フラグ
	bool playing = true;
};


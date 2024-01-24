#include "CAnimation.h"

void CAnimation::Update()
{
	// 再生フラグが立っていないなら更新せずに返す
	if (!playing)
	{
		return;
	}

	// 表示させるコマIDを取得
	int animID = animationTable[(int)anim_pattern][(int)animCounter];

	// 表示するコマを計算
	uv.x = animID % spritU * uv_movement.x;
	uv.y = animID / spritU * uv_movement.y;

	// カウンターを進める
	animCounter += animationSpeed;

	// 終端がループなら
	if (animationTable[(int)anim_pattern][(int)animCounter] == ANIM_LOOP)
	{
		// 
		animCounter = 0.0f;
	}
	// 終端がストップなら
	else if (animationTable[(int)anim_pattern][(int)animCounter] == ANIM_STOP)
	{
		// 再生状態フラグを下げる
		playing = false;
	}
}

void CAnimation::SetAnimationSpeed(float sp)
{
	// アニメーションのスピードを設定
	animationSpeed = sp;
}

void CAnimation::SetAnimationPattern(ANIM_PATTERN pattern)
{
	// パターンの設定
	anim_pattern = pattern;
}

void CAnimation::SetMovementUV(FLOAT_XY movement)
{
	// uvの移動量
	uv_movement = movement;
}

void CAnimation::SetSpritU(int sprit)
{
	// 設定された値が0以下なら1に戻す
	if (spritU <= 0)
	{
		sprit = 1;
	}
	// 横の分割数の設定
	spritU = sprit;
}

void CAnimation::PlayAnimation()
{
	// アニメーションの再生状態フラグを上げる
	playing = true;
}

void CAnimation::StopAnimation()
{
	// アニメーションの再生状態フラグを下げる
	playing = false;
}

void CAnimation::ResetAnimation()
{
	// カウンターを0に戻す
	animCounter = 0.0f;
}

FLOAT_XY CAnimation::GetUV()
{
	return uv;
}

#include "CSmoothing.h"
#include <iostream>

CSmoothing::CSmoothing()
{
	// 係数,ポインタの初期化
	alpha = 0.0f;
	posT = nullptr;
	posF = nullptr;
}

CSmoothing::~CSmoothing()
{
}

void CSmoothing::Update()
{
	// 初期化が行われていない場合は処理を行わない
	if (posF != nullptr && posT != nullptr)
	{
		// スムーズを適応
		*posF = alpha * (*posT) + (1 - alpha) * (*posF);
	}
}

void CSmoothing::InitSmooth(float* target_pos, float* follow_pos, float coef)
{
	// 追従対象の座標ポインタを設定
	posT = target_pos;
	// 追従させる座標ポインタを設定
	posF = follow_pos;
	// スムージング係数を設定
	if (coef < 0.0f)
	{
		// 0以下に設定されていた場合補正する
		coef = 0.0f;
	}
	else if(coef > 1.0f)
	{
		// 1以上に設定されていた場合補正する
		coef = 1.0f;
	}
	alpha = coef;
}

void CSmoothing::ChangeSmoothCoef(float coef)
{
	// スムージング係数を設定
	if (coef < 0.0f)
	{
		// 0以下に設定されていた場合補正する
		coef = 0;
	}
	else if (coef > 1.0f)
	{
		// 1以上に設定されていた場合補正する
		coef = 1.0f;
	}
	alpha = coef;
}

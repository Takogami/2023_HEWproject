#pragma once
class CSmoothing
{
private:
	// スムージング係数
	float alpha;
	// 追従対象の座標
	float* posT;
	// 変更する座標
	float* posF;

public:
	// コンストラクタ
	CSmoothing();
	// デストラクタ
	~CSmoothing();
	// 更新
	void Update();
	// スムージング初期化
	// 引数1:追従対象の座標 引数2:変更する座標 引数3:スムーズ係数(0～1)
	void InitSmooth(float* target_pos,float* follow_pos, float coef);
	// スムージング係数の変更
	void ChangeSmoothCoef(float coef);
};


#pragma once
#include<math.h>
#include<map>

// 円周率
#define PI (3.141592f)

// 実行状態識別列挙型
enum class STATE
{
	WAIT,	// 待ち状態
	UPDATE,	// 更新
	END		// 終了
};

enum class EASE
{
	easeInSine,
	easeOutSine,
	easeInOutSine,
	easeInQuad,
	easeOutQuad,
	easeInOutQuad,
	easeInCubic,
	easeOutCubic,
	easeInOutCubic,
	easeInQuart,
	easeOutQuart,
	easeInOutQuart,
	easeInQuint,
	easeOutQuint,
	easeInOutQuint,
	easeInExpo,
	easeOutExpo,
	easeInOutExpo,
	easeInCirc,
	easeOutCirc,
	easeInOutCirc,
	easeInBack,
	easeOutBack,
	easeInOutBack,
	easeInElastic,
	easeOutElastic,
	easeInOutElastic,
	easeInBounce,
	easeOutBounce,
	easeInOutBounce
};

inline double easeInSine(double x) { return 1 - cos((x * PI) / 2); }
inline double easeOutSine(double x) { return sin((x * PI) / 2); }
inline double easeInOutSine(double x) { return -(cos(PI * x) - 1) / 2; }
inline double easeInCubic(double x) { return x * x * x; }
inline double easeOutCubic(double x) { return 1 - pow(1 - x, 3); }
inline double easeInOutCubic(double x) { return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
inline double easeInQuint(double x) { return x * x * x * x * x; }
inline double easeOutQuint(double x) { return 1 - pow(1 - x, 5); }
inline double easeInOutQuint(double x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2; }
inline double easeInCirc(double x) { return 1 - sqrt(1 - pow(x, 2)); }
inline double easeOutCirc(double x) { return sqrt(1 - pow(x - 1, 2)); }
inline double easeInOutCirc(double x) { return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2; }
inline double easeInElastic(double x) { const double c4 = (2 * PI) / 3; return x == 0 ? 0 : x == 1 ? 1 : -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4); }
inline double easeOutElastic(double x) { const double c4 = (2 * PI) / 3; return x == 0 ? 0 : x == 1 ? 1 : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1; }
inline double easeInOutElastic(double x) { const double c5 = (2 * PI) / 4.5; return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2 : (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1; }
inline double easeInQuad(double x) { return x * x; }
inline double easeOutQuad(double x) { return 1 - (1 - x) * (1 - x); }
inline double easeInOutQuad(double x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2; }
inline double easeInQuart(double x) { return x * x * x * x; }
inline double easeOutQuart(double x) { return 1 - pow(1 - x, 4); }
inline double easeInOutQuart(double x) { return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2; }
inline double easeInExpo(double x) { return x == 0 ? 0 : pow(2, 10 * x - 10); }
inline double easeOutExpo(double x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
inline double easeInOutExpo(double x) { return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? pow(2, 20 * x - 10) / 2 : (2 - pow(2, -20 * x + 10)) / 2; }
inline double easeInBack(double x) { const double c1 = 1.70158; const double c3 = c1 + 1; return c3 * x * x * x - c1 * x * x; }
inline double easeOutBack(double x) { const double c1 = 1.70158; const double c3 = c1 + 1; return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2); }
inline double easeInOutBack(double x) { const double c1 = 1.70158; const double c2 = c1 * 1.525; return x < 0.5 ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2 : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2; }
inline double easeOutBounce(double x) { const double n1 = 7.5625; const double d1 = 2.75; if (x < 1 / d1) { return n1 * x * x; } else if (x < 2 / d1) { return n1 * (x -= 1.5 / d1) * x + 0.75; } else if (x < 2.5 / d1) { return n1 * (x -= 2.25 / d1) * x + 0.9375; } else { return n1 * (x -= 2.625 / d1) * x + 0.984375; } }
inline double easeInBounce(double x) { return 1 - easeOutBounce(1 - x); }
inline double easeInOutBounce(double x) { return x < 0.5 ? (1 - easeOutBounce(1 - 2 * x)) / 2 : (1 + easeOutBounce(2 * x - 1)) / 2; }

// 関数ポインタの定義
using EaseAdress = double(*)(double);

//辞書型を用意して列挙型と関数ポインタを結びつける
static std::map<EASE, EaseAdress>EaseDictionary =
{
	{EASE::easeInSine,		&easeInSine},
	{EASE::easeOutSine,		&easeOutSine},
	{EASE::easeInSine,		&easeInSine},
	{EASE::easeOutSine,		&easeOutSine},
	{EASE::easeInOutSine,	&easeInOutSine},
	{EASE::easeInQuad,		&easeInQuad},
	{EASE::easeOutQuad,		&easeOutQuad},
	{EASE::easeInOutQuad,	&easeInOutQuad},
	{EASE::easeInCubic,		&easeInCubic},
	{EASE::easeOutCubic,	&easeOutCubic},
	{EASE::easeInOutCubic,	&easeInOutCubic},
	{EASE::easeInQuart,		&easeInQuart},
	{EASE::easeOutQuart,	&easeOutQuart},
	{EASE::easeInOutQuart,	&easeInOutQuart},
	{EASE::easeInQuint,		&easeInQuint},
	{EASE::easeOutQuint,	&easeOutQuint},
	{EASE::easeInOutQuint,	&easeInOutQuint},
	{EASE::easeInExpo,		&easeInExpo},
	{EASE::easeOutExpo,		&easeOutExpo},
	{EASE::easeInOutExpo,	&easeInOutExpo},
	{EASE::easeInCirc,		&easeInCirc},
	{EASE::easeOutCirc,		&easeOutCirc},
	{EASE::easeInOutCirc,	&easeInOutCirc},
	{EASE::easeInBack,		&easeInBack},
	{EASE::easeOutBack,		&easeOutBack},
	{EASE::easeInOutBack,	&easeInOutBack},
	{EASE::easeInElastic,	&easeInElastic},
	{EASE::easeOutElastic,	&easeOutElastic},
	{EASE::easeInOutElastic,&easeInOutElastic},
	{EASE::easeInBounce,	&easeInBounce},
	{EASE::easeOutBounce,	&easeOutBounce},
	{EASE::easeInOutBounce,	&easeInOutBounce}
};

class CEase
{
private:
	// 状態
	STATE state;
	// 開始座標
	float* startPos;
	// 終了座標
	float endPos;
	// 実行時間
	float duration;
	// フレームカウンター
	int count;
	// 開始までの時間(フレーム)
	int startTime;

	float start;

	// イージング関数ポインタ
	EaseAdress Easeing = &easeInSine;

public:
	// 引数1 : スタート位置 引数2 : 終了位置 引数3 : 時間 引数4 : 開始時間 引数5 : イージングの種類
	void Init(float * start, float end, float dur, int delay, EASE ease);
	// 更新
	void Update();
	// 現在の状態を取得
	STATE GetState();
};


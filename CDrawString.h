#pragma once

#include "DirectWrite.h"
#include "direct3d.h"
#include <vector>

// フォントスタイル
enum class FONT_STYLE
{
	NORMAL,		// 通常
	OBLIQUE,	// 斜体
	ITALIC,		// イタリック体
};

// フォントの太さ
enum class FONT_WEIGHT
{
    THIN = 100,			// 最小
    EXTRA_LIGHT = 200,
    ULTRA_LIGHT = 200,
    LIGHT = 300,
    SEMI_LIGHT = 350,
    NORMAL = 400,		// 通常
    REGULAR = 400,		// 通常
    MEDIUM = 500,
    DEMI_BOLD = 600,
    SEMI_BOLD = 600,
    BOLD = 700,
    EXTRA_BOLD = 800,
    ULTRA_BOLD = 800,
    BLACK = 900,
    HEAVY = 900,
    EXTRA_BLACK = 950,	// 最大
    ULTRA_BLACK = 950	// 最大
};

class CDrawString
{
private:
	// 設定された文字列
	std::vector<std::string> drawString;
	// 行数カウント
	int lineCount = 0;
	
	// 文字列の表示位置
	FLOAT_XY position = { 0.0f, 0.0f };
	// 影の設定 trueで影を表示
	bool shadow = false;
	// フォントのパラメータ
	FontData param;
	// 行間
	FLOAT lineSpacing = 0.0f;

	// 文字の表示状態
	bool isActive = true;

public:
	// 描画する文字列を設定
	void SetString(std::string _drawString);
	// 描画するフォントのサイズを設定
	void SetFontSize(FLOAT size);
	// フォントの種類を設定
	void SetFont(FontID id);
	// 描画位置の設定（px単位で指定）
	void SetPosition(FLOAT_XY pos);
	// 文字色の設定（透明度を変更しない場合は a の指定は必要ありません）
	void SetFontColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0f);
	// 影の設定（透明度を変更しない場合は a の指定は必要ありません）
	void SetShadow(FLOAT_XY offset ,FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0f);
	// フォントの太さを設定
	void SetFontWeight(FONT_WEIGHT fontWeight);
	// フォントのスタイルを設定
	void SetFontStyle(FONT_STYLE fontStyle);
	// 改行時の行間を設定
	void SetLineSpacing(FLOAT spacing);
	// 文字列を描画を行うか否かを設定
	void SetActive(bool isActive);

	// 文字列の描画
	void Draw();
};


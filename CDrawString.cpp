#include "CDrawString.h"

void CDrawString::SetString(std::string _drawString)
{
	// 配列の初期化を行う
	drawString.resize(0);
	// メモリ領域を合わせる
	drawString.shrink_to_fit();
	// 行数カウントを0に戻す
	lineCount = 0;

	// 改行コードがあるかを確認
	std::size_t newlinePos = _drawString.find('\n');
	// 改行コードが無いなら渡された文字列をそのまま格納
	if (newlinePos == std::string::npos)
	{
		// 行を追加する
		drawString.resize(drawString.size() + 1);
		lineCount++;
		// 配列の先頭にそのまま格納
		drawString[0] = _drawString;
		return;
	}

	// 改行コードがなくなるまで繰り返す
	for (lineCount = 0; newlinePos != std::string::npos; lineCount++)
	{
		// 改行コードまでの文字列サイズを取得する
		newlinePos = _drawString.find('\n');
		// 行を追加する
		drawString.resize(drawString.size() + 1);
		// 改行コードまでの文字列を保存
		drawString[lineCount] = _drawString.substr(0, newlinePos);
		// 格納した文字列を切り離して残りの文字を格納
		_drawString = _drawString.erase(0, newlinePos + 1);
	}
}

void CDrawString::SetFontSize(FLOAT size)
{
	param.fontSize = size;
}

void CDrawString::SetFont(FontID id)
{
	// idからフォントを取得する
	param.font = directWrite->GetFontName((int)id);
}

void CDrawString::SetPosition(FLOAT_XY pos)
{
	position = pos;
}

void CDrawString::SetFontColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	// D2D1_COLOR_F型でパラメータにセット
	param.Color = { r, g, b, a };
}

void CDrawString::SetShadow(FLOAT_XY offset, FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	// 影をアクティブに設定する
	shadow = true;
	// D2D1_COLOR_F型でパラメータにセット
	param.shadowColor = { r, g, b, a };
	// D2D1_POINT_2F型でパラメータにセット
	param.shadowOffset = { offset.x, offset.y };
}

void CDrawString::SetFontWeight(FONT_WEIGHT fontWeight)
{
	param.fontWeight = (DWRITE_FONT_WEIGHT)fontWeight;
}

void CDrawString::SetFontStyle(FONT_STYLE fontStyle)
{
	// DWRITE_FONT_STYLEにキャストして渡す
	param.fontStyle = (DWRITE_FONT_STYLE)fontStyle;
}

void CDrawString::SetLineSpacing(FLOAT spacing)
{
	lineSpacing = spacing;
}

void CDrawString::SetActive(bool isAct)
{
	isActive = isAct;
}

void CDrawString::Draw()
{
	// アクティブでない または 文字列が設定されていないなら描画処理を行わない
	if (!isActive || drawString.size() == 0)
	{
		return;
	}

	// 指定されたパラメータを反映
	fontData = param;
	// フォントのセット
	directWrite->SetFont(fontData);

	// 初期位置を保存
	FLOAT_XY defPos = position;

	// パラメータを渡して文字列の描画を行う
	for (int i = 0; lineCount > i; i++)
	{
		// directWhiteで描画する
		directWrite->DrawString(this->drawString[i], position.x, position.y, D2D1_DRAW_TEXT_OPTIONS_NONE, shadow);
		// 描画位置、フォントサイズ、行間から位置を決定する
		position.y = position.y + fontData.fontSize + lineSpacing;
	}

	// 文字列描画位置をデフォルトに戻す
	position = defPos;
}

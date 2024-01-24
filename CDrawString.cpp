#include "CDrawString.h"

void CDrawString::SetString(std::string _drawString)
{
	drawString = _drawString;
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

void CDrawString::SetActive(bool isAct)
{
	isActive = isAct;
}

void CDrawString::Draw()
{
	// アクティブでないなら描画処理を行わない
	if (!isActive)
	{
		return;
	}

	// 指定されたパラメータを反映
	fontData = param;
	// フォントのセット
	directWrite->SetFont(fontData);
	// パラメータを渡して文字列の描画を行う
	directWrite->DrawString(this->drawString, position.x, position.y, D2D1_DRAW_TEXT_OPTIONS_NONE, shadow);
}

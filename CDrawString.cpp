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
	// id����t�H���g���擾����
	param.font = directWrite->GetFontName((int)id);
}

void CDrawString::SetPosition(FLOAT_XY pos)
{
	position = pos;
}

void CDrawString::SetFontColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	// D2D1_COLOR_F�^�Ńp�����[�^�ɃZ�b�g
	param.Color = { r, g, b, a };
}

void CDrawString::SetShadow(FLOAT_XY offset, FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	// �e���A�N�e�B�u�ɐݒ肷��
	shadow = true;
	// D2D1_COLOR_F�^�Ńp�����[�^�ɃZ�b�g
	param.shadowColor = { r, g, b, a };
	// D2D1_POINT_2F�^�Ńp�����[�^�ɃZ�b�g
	param.shadowOffset = { offset.x, offset.y };
}

void CDrawString::SetFontWeight(FONT_WEIGHT fontWeight)
{
	param.fontWeight = (DWRITE_FONT_WEIGHT)fontWeight;
}

void CDrawString::SetFontStyle(FONT_STYLE fontStyle)
{
	// DWRITE_FONT_STYLE�ɃL���X�g���ēn��
	param.fontStyle = (DWRITE_FONT_STYLE)fontStyle;
}

void CDrawString::SetActive(bool isAct)
{
	isActive = isAct;
}

void CDrawString::Draw()
{
	// �A�N�e�B�u�łȂ��Ȃ�`�揈�����s��Ȃ�
	if (!isActive)
	{
		return;
	}

	// �w�肳�ꂽ�p�����[�^�𔽉f
	fontData = param;
	// �t�H���g�̃Z�b�g
	directWrite->SetFont(fontData);
	// �p�����[�^��n���ĕ�����̕`����s��
	directWrite->DrawString(this->drawString, position.x, position.y, D2D1_DRAW_TEXT_OPTIONS_NONE, shadow);
}

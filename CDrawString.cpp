#include "CDrawString.h"

void CDrawString::SetString(std::string _drawString)
{
	// �z��̏��������s��
	drawString.resize(0);
	// �������̈�����킹��
	drawString.shrink_to_fit();
	// �s���J�E���g��0�ɖ߂�
	lineCount = 0;

	// ���s�R�[�h�����邩���m�F
	std::size_t newlinePos = _drawString.find('\n');
	// ���s�R�[�h�������Ȃ�n���ꂽ����������̂܂܊i�[
	if (newlinePos == std::string::npos)
	{
		// �s��ǉ�����
		drawString.resize(drawString.size() + 1);
		lineCount++;
		// �z��̐擪�ɂ��̂܂܊i�[
		drawString[0] = _drawString;
		return;
	}

	// ���s�R�[�h���Ȃ��Ȃ�܂ŌJ��Ԃ�
	for (lineCount = 0; newlinePos != std::string::npos; lineCount++)
	{
		// ���s�R�[�h�܂ł̕�����T�C�Y���擾����
		newlinePos = _drawString.find('\n');
		// �s��ǉ�����
		drawString.resize(drawString.size() + 1);
		// ���s�R�[�h�܂ł̕������ۑ�
		drawString[lineCount] = _drawString.substr(0, newlinePos);
		// �i�[�����������؂藣���Ďc��̕������i�[
		_drawString = _drawString.erase(0, newlinePos + 1);
	}
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
	// �A�N�e�B�u�łȂ� �܂��� �����񂪐ݒ肳��Ă��Ȃ��Ȃ�`�揈�����s��Ȃ�
	if (!isActive || drawString.size() == 0)
	{
		return;
	}

	// �w�肳�ꂽ�p�����[�^�𔽉f
	fontData = param;
	// �t�H���g�̃Z�b�g
	directWrite->SetFont(fontData);

	// �����ʒu��ۑ�
	FLOAT_XY defPos = position;

	// �p�����[�^��n���ĕ�����̕`����s��
	for (int i = 0; lineCount > i; i++)
	{
		// directWhite�ŕ`�悷��
		directWrite->DrawString(this->drawString[i], position.x, position.y, D2D1_DRAW_TEXT_OPTIONS_NONE, shadow);
		// �`��ʒu�A�t�H���g�T�C�Y�A�s�Ԃ���ʒu�����肷��
		position.y = position.y + fontData.fontSize + lineSpacing;
	}

	// ������`��ʒu���f�t�H���g�ɖ߂�
	position = defPos;
}

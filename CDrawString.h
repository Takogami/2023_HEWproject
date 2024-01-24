#pragma once

#include "DirectWrite.h"
#include "direct3d.h"
#include <vector>

// �t�H���g�X�^�C��
enum class FONT_STYLE
{
	NORMAL,		// �ʏ�
	OBLIQUE,	// �Α�
	ITALIC,		// �C�^���b�N��
};

// �t�H���g�̑���
enum class FONT_WEIGHT
{
    THIN = 100,			// �ŏ�
    EXTRA_LIGHT = 200,
    ULTRA_LIGHT = 200,
    LIGHT = 300,
    SEMI_LIGHT = 350,
    NORMAL = 400,		// �ʏ�
    REGULAR = 400,		// �ʏ�
    MEDIUM = 500,
    DEMI_BOLD = 600,
    SEMI_BOLD = 600,
    BOLD = 700,
    EXTRA_BOLD = 800,
    ULTRA_BOLD = 800,
    BLACK = 900,
    HEAVY = 900,
    EXTRA_BLACK = 950,	// �ő�
    ULTRA_BLACK = 950	// �ő�
};

class CDrawString
{
private:
	// �ݒ肳�ꂽ������
	std::vector<std::string> drawString;
	// �s���J�E���g
	int lineCount = 0;
	
	// ������̕\���ʒu
	FLOAT_XY position = { 0.0f, 0.0f };
	// �e�̐ݒ� true�ŉe��\��
	bool shadow = false;
	// �t�H���g�̃p�����[�^
	FontData param;
	// �s��
	FLOAT lineSpacing = 0.0f;

	// �����̕\�����
	bool isActive = true;

public:
	// �`�悷�镶�����ݒ�
	void SetString(std::string _drawString);
	// �`�悷��t�H���g�̃T�C�Y��ݒ�
	void SetFontSize(FLOAT size);
	// �t�H���g�̎�ނ�ݒ�
	void SetFont(FontID id);
	// �`��ʒu�̐ݒ�ipx�P�ʂŎw��j
	void SetPosition(FLOAT_XY pos);
	// �����F�̐ݒ�i�����x��ύX���Ȃ��ꍇ�� a �̎w��͕K�v����܂���j
	void SetFontColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0f);
	// �e�̐ݒ�i�����x��ύX���Ȃ��ꍇ�� a �̎w��͕K�v����܂���j
	void SetShadow(FLOAT_XY offset ,FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0f);
	// �t�H���g�̑�����ݒ�
	void SetFontWeight(FONT_WEIGHT fontWeight);
	// �t�H���g�̃X�^�C����ݒ�
	void SetFontStyle(FONT_STYLE fontStyle);
	// ���s���̍s�Ԃ�ݒ�
	void SetLineSpacing(FLOAT spacing);
	// �������`����s�����ۂ���ݒ�
	void SetActive(bool isActive);

	// ������̕`��
	void Draw();
};


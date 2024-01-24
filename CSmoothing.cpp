#include "CSmoothing.h"
#include <iostream>

CSmoothing::CSmoothing()
{
	// �W��,�|�C���^�̏�����
	alpha = 0.0f;
	posT = nullptr;
	posF = nullptr;
}

CSmoothing::~CSmoothing()
{
}

void CSmoothing::Update()
{
	// ���������s���Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (posF != nullptr && posT != nullptr)
	{
		// �X���[�Y��K��
		*posF = alpha * (*posT) + (1 - alpha) * (*posF);
	}
}

void CSmoothing::InitSmooth(float* target_pos, float* follow_pos, float coef)
{
	// �Ǐ]�Ώۂ̍��W�|�C���^��ݒ�
	posT = target_pos;
	// �Ǐ]��������W�|�C���^��ݒ�
	posF = follow_pos;
	// �X���[�W���O�W����ݒ�
	if (coef < 0.0f)
	{
		// 0�ȉ��ɐݒ肳��Ă����ꍇ�␳����
		coef = 0.0f;
	}
	else if(coef > 1.0f)
	{
		// 1�ȏ�ɐݒ肳��Ă����ꍇ�␳����
		coef = 1.0f;
	}
	alpha = coef;
}

void CSmoothing::ChangeSmoothCoef(float coef)
{
	// �X���[�W���O�W����ݒ�
	if (coef < 0.0f)
	{
		// 0�ȉ��ɐݒ肳��Ă����ꍇ�␳����
		coef = 0;
	}
	else if (coef > 1.0f)
	{
		// 1�ȏ�ɐݒ肳��Ă����ꍇ�␳����
		coef = 1.0f;
	}
	alpha = coef;
}

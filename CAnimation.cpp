#include "CAnimation.h"

void CAnimation::Update()
{
	// �Đ��t���O�������Ă��Ȃ��Ȃ�X�V�����ɕԂ�
	if (!playing)
	{
		return;
	}

	// �\��������R�}ID���擾
	int animID = animationTable[(int)anim_pattern][(int)animCounter];

	// �\������R�}���v�Z
	uv.x = animID % spritU * uv_movement.x;
	uv.y = animID / spritU * uv_movement.y;

	// �J�E���^�[��i�߂�
	animCounter += animationSpeed;

	// �I�[�����[�v�Ȃ�
	if (animationTable[(int)anim_pattern][(int)animCounter] == ANIM_LOOP)
	{
		// 
		animCounter = 0.0f;
	}
	// �I�[���X�g�b�v�Ȃ�
	else if (animationTable[(int)anim_pattern][(int)animCounter] == ANIM_STOP)
	{
		// �Đ���ԃt���O��������
		playing = false;
	}
}

void CAnimation::SetAnimationSpeed(float sp)
{
	// �A�j���[�V�����̃X�s�[�h��ݒ�
	animationSpeed = sp;
}

void CAnimation::SetAnimationPattern(ANIM_PATTERN pattern)
{
	// �p�^�[���̐ݒ�
	anim_pattern = pattern;
}

void CAnimation::SetMovementUV(FLOAT_XY movement)
{
	// uv�̈ړ���
	uv_movement = movement;
}

void CAnimation::SetSpritU(int sprit)
{
	// �ݒ肳�ꂽ�l��0�ȉ��Ȃ�1�ɖ߂�
	if (spritU <= 0)
	{
		sprit = 1;
	}
	// ���̕������̐ݒ�
	spritU = sprit;
}

void CAnimation::PlayAnimation()
{
	// �A�j���[�V�����̍Đ���ԃt���O���グ��
	playing = true;
}

void CAnimation::StopAnimation()
{
	// �A�j���[�V�����̍Đ���ԃt���O��������
	playing = false;
}

void CAnimation::ResetAnimation()
{
	// �J�E���^�[��0�ɖ߂�
	animCounter = 0.0f;
}

FLOAT_XY CAnimation::GetUV()
{
	return uv;
}

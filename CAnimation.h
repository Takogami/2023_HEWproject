#pragma once

#include <vector>
#include "direct3d.h"

// �A�j���[�V�����I�[
#define ANIM_LOOP	(-1)	// �A�j���[�V���������[�v
#define ANIM_STOP	(-2)	// �A�j���[�V�������X�g�b�v

// �A�j���[�V�����p�^�[���񋓌^
enum class ANIM_PATTERN
{
	NO_ANIM = 0,
	TEST,
};

class CAnimation
{
public:
	// �X�V
	void Update();
	// �A�j���[�V�����̃X�s�[�h��ݒ�
	void SetAnimationSpeed(float sp);
	// �A�j���[�V�����p�^�[���̐ݒ�
	void SetAnimationPattern(ANIM_PATTERN pattern);
	// �A�j���[�V�����p�^�[���̐ݒ�
	void SetMovementUV(FLOAT_XY movement);
	// ���������̐ݒ�
	void SetSpritU(int sprit);
	// �A�j���[�V�����̍Đ�
	void PlayAnimation();
	// �A�j���[�V�����̒�~
	void StopAnimation();
	// �A�j���[�V�����̐i�s�󋵂����Z�b�g
	void ResetAnimation();
	// ���݂�uv���擾
	FLOAT_XY GetUV();

private:
	// �A�j���[�V�����e�[�u��
	std::vector<std::vector<int>> animationTable
	{
		{ 0, ANIM_LOOP },
		{ 6, 7, 8, 7, ANIM_LOOP},
	};

	// �A�j���[�V�����X�s�[�h
	float animationSpeed = 0.0f;
	// �A�j���[�V�����p�^�[��
	ANIM_PATTERN anim_pattern = ANIM_PATTERN::NO_ANIM;
	// ���݂�uv���W
	FLOAT_XY uv = { 0.0f, 0.0f };
	// uv�ړ���
	FLOAT_XY uv_movement = { 0.0f, 0.0f };
	// �A�j���[�V�����i�s�J�E���^�[
	float animCounter = 0;
	// ��������
	int spritU = 1;
	// �Đ����t���O
	bool playing = true;
};


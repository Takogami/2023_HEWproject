#pragma once

#include <vector>
#include "direct3d.h"

// �A�j���[�V�����I�[
#define ANIM_LOOP	(-1)	// �A�j���[�V���������[�v
#define ANIM_STOP	(-2)	// �A�j���[�V�������X�g�b�v
#define ANIM_FINISH	(-3)	// �A�j���[�V�������I��

// �A�j���[�V�����p�^�[���񋓌^
enum class ANIM_PATTERN
{
	NO_ANIM = 0,
	TEST,
	LEFTWALK,	//���ɕ���
	RIGHTWALK,	//�E�ɕ���
	FALLDOWN,	//�|���
	GETUP,		//�N���オ��
	BREAKLEFT,	//���ɐ܂��
	BREAKRIGHT,	//�E�ɐ܂��
	FIXLEFT,	//���ɋN���オ��
	FIXRIGHT,	//�E�ɋN���オ��
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
	// �c�������̐ݒ�
	void SetSpritV(int sprit);
	// �A�j���[�V�����̍Đ�
	void PlayAnimation();
	// �A�j���[�V�����̒�~
	void StopAnimation();
	// �A�j���[�V�����̐i�s�󋵂����Z�b�g
	void ResetAnimation();
	// �J�ڃA�j���[�V����������ݒ�
	void SetIsAnimation(bool anim);
	// �J�ڃA�j���[�V�����̍Đ���Ԃ��擾
	bool GetIsAnimation();
	// ���݂�uv���擾
	FLOAT_XY GetUV();

private:
	// �A�j���[�V�����e�[�u��
	std::vector<std::vector<int>> animationTable
	{
		{ 0, ANIM_STOP },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ANIM_LOOP},
		{ 5,  4,  3, 4, ANIM_LOOP},
		{ 0,  1,  2, 1, ANIM_LOOP},
		{ 12, 13, 14,	ANIM_STOP},
		{ 15, 16, 17,	ANIM_STOP},
		{ 6,  7,  8,	ANIM_STOP},
		{ 9,  10, 11,	ANIM_STOP},
		{ 8,  7,  6,	ANIM_STOP},
		{ 11, 10, 9,	ANIM_STOP},


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
	// �c������
	int spritV = 1;
	// �Đ����t���O
	bool playing = true;
	//�J�ڃA�j���[�V�����t���O
	bool isanim = false;
};


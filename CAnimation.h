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
	JAMP,		//�W�����v
	FLAYING,	//���ł���		
	FALL,		//�|��Ă�����

	BOOK,		//�{�̓���
	BOOK_REVERSE,
	ENEMY_MOVE,
	ENEMY_MOVE_R,
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

		{ 9, 8, 7, 6, 5, 6, 7, 8, ANIM_LOOP},	//���ɕ���
		{ 0, 1, 2, 3, 4, 3, 2, 1, ANIM_LOOP},	//�E�ɕ���
		{ 20, 21, 22, 23, 24, ANIM_STOP},	//�|���
		{ 25, 26, 27, 28, 29, ANIM_STOP},	//�N���オ��
		{ 10, 11, 12, 13, 14, ANIM_STOP},	//���ɐ܂��
		{ 15, 16, 17, 18, 19, ANIM_STOP},	//�E�ɐ܂��
		{ 14, 13, 12, 11, 10, ANIM_STOP},	//���ɋN���オ��
		{ 19, 18, 17, 16, 15, ANIM_STOP},	//�E�ɋN���オ��
		{ 42, 43, 44, 43, 42, 41, 40, ANIM_STOP},	//�W�����v
		{ 45, 46, 47, 48, 49, 48, 47, 46, ANIM_LOOP},	//���ł���
		{ 10, ANIM_STOP },	//�|��Ă�����

		{ 0, 1, 2, 3, 4, 0, ANIM_STOP},	//�{�̓���
		{ 0, 4, 3, 2, 1, 0, ANIM_STOP},	//�{�t
		{ 0, 0, 0, 1, 2, 1, ANIM_LOOP},
		{ 5, 5, 5, 4, 3, 4, ANIM_LOOP},

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


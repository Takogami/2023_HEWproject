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
	IDOL_R,
	IDOL_L,
	PLAYER_DOWN,
	LEFTWALK,	//���ɕ���
	RIGHTWALK,	//�E�ɕ���
	FALLDOWN,	//�|���
	FALLDOWN_L,	//�|���i���j
	GETUP,		//�N���オ��
	GETUP_L,	//�N���オ��i���j
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
	WIND_UP,
	WIND_LEFT,
	WIND_RIGHT,
	FADEOUT_ANIM,
	FADEIN_ANIM,
	DAMAGE
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

		{ 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 33, 33, 32, 32, 31, 31, ANIM_LOOP},		// �E�����
		{ 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 38, 38, 37, 37, 36, 36, ANIM_LOOP},		// �������

		// �_�E���A�j���[�V����
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 42, 43, 44, 44, 43, 42, 41, 40, ANIM_STOP},

		{ 9, 8, 7, 6, 5, 6, 7, 8, ANIM_LOOP},	//���ɕ���
		{ 0, 1, 2, 3, 4, 3, 2, 1, ANIM_LOOP},	//�E�ɕ���
		{ 20, 21, 22, 23, 24, ANIM_STOP},	//�|���
		{ 29, 28, 27, 26, 25, ANIM_STOP},	//�|���i���j
		{ 24, 23, 22, 21, 20, ANIM_STOP},	//�N���オ��
		{ 25, 26, 27, 28, 29, ANIM_STOP},	//�N���オ��(��)
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

		// ��@�A�j���[�V����
		{0, 1, ANIM_LOOP},
		{2, 3, ANIM_LOOP},
		{4, 5, ANIM_LOOP},

		// �t�F�[�h�p�A�j���[�V����
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, ANIM_STOP},			// �t�F�[�h�A�E�g
		{21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, ANIM_STOP},// �t�F�[�h�C��

		// �_���[�W�G�t�F�N�g�p
		{0, 1, 2, 3, 4, 5, 6, ANIM_STOP},
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


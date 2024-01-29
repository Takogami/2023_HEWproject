#pragma once
#include <time.h>

// �^�C�}�[�̏��
enum class TIMER_STATE
{
	WAIT,
	UPDATE,
	PAUSE,
	END,
};

// �J�E���g�A�b�v���J�E���g�_�E����
enum class TIMER_MODE
{
	COUNT_UP,
	COUNT_DOWN,
};

// 
class CTimer
{
private:
	// �^�C�}�[�̉ғ����
	TIMER_STATE state = TIMER_STATE::WAIT;
	// �^�C�}�[�̃��[�h
	TIMER_MODE mode;

	// �X�^�[�g�̎���
	time_t startTime;
	// ���݂̎���
	time_t nowTime;
	// �o�ߎ��Ԏ���
	time_t progressTime;
	// ���݂̃^�C�}�[�Ōv��������
	time_t progressCountTime;
	// �J�E���g���鎞��
	time_t countTime;
	// �^�C�}�[�̃��[�h�ɉ����Ă̍X�V����
	void TimerModeUpdate();

public:
	// �^�C�}�[�̃Z�b�g(������)
	// ����1 : �J�E���g���鎞�� ����2 : ���[�h�ݒ�
	void InitTimer(time_t CountTime, TIMER_MODE TimerMode);
	// �^�C�}�[�̍X�V
	void Update();
	// �^�C�}�[���J�n
	void StartTimer() { state = TIMER_STATE::UPDATE; }
	// �^�C�}�[���ꎞ��~
	void PauseTimer() { state = TIMER_STATE::PAUSE; }
	// �^�C�}�[�̍ĊJ
	void ResumeTimer();
	// �v�������Ԃ��擾
	time_t GetTime() { return progressCountTime; }
	// �o�ߎ��Ԃ��擾
	time_t GetProgressTime() { return progressTime; }
	// �^�C�}�[�̏�Ԃ����擾
	TIMER_STATE GetTimerState() { return state; };
};


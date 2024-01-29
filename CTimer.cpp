#include "CTimer.h"

void CTimer::InitTimer(time_t CountTime, TIMER_MODE TimerMode)
{
    // �e�p�����[�^�̐ݒ�
    countTime = CountTime;
    mode = TimerMode;

    // ������
    state = TIMER_STATE::WAIT;
    startTime = time(NULL);

    // ���[�h�ɍ��킹�ď����l��ύX
    if (mode == TIMER_MODE::COUNT_DOWN)
    {
        progressCountTime = countTime;
    }
    else
    {
        progressCountTime = 0;
    }
    progressTime = 0;
}

void CTimer::Update()
{
    // 
    switch (state)
    {
        // �J�n�҂�
    case TIMER_STATE::WAIT:
        // �X�^�[�g�̎��Ԃ��擾��������
        startTime = time(NULL);
        break;

        // ���쒆
    case TIMER_STATE::UPDATE:
        // �e���[�h�ɉ������X�V�������s��
        TimerModeUpdate();
        break;

        // 1����~��
    case TIMER_STATE::PAUSE:
        break;

        // �I��
    case TIMER_STATE::END:
        break;
    }
}

void CTimer::ResumeTimer()
{
    if (state == TIMER_STATE::PAUSE)
    {
        // �ꎞ��~���̌o�ߎ��Ԃ��v�Z���A�J�n���Ԃ𒲐�����
        // �ꎞ��~���̎���
        time_t pauseDuration = time(NULL) - nowTime;
        // �J�n���Ԃ𒲐�
        startTime += pauseDuration;
        // �^�C�}�[���ĊJ
        state = TIMER_STATE::UPDATE;
    }
}

void CTimer::TimerModeUpdate()
{
    switch (mode)
    {
        // �J�E���g�A�b�v
    case TIMER_MODE::COUNT_UP:

        // ���݂̎��Ԃ��擾
        nowTime = time(NULL);
        // �o�ߎ��Ԃ��v�Z
        progressTime = nowTime - startTime;
        // �v�������Ԃ�ۑ�
        progressCountTime = progressTime;

        // �ݒ肳�ꂽ���Ԍo�߂����Ȃ�I����Ԃɂ���
        if (progressCountTime >= countTime)
        {
            state = TIMER_STATE::END;
        }
        break;

        // �J�E���g�_�E��
    case TIMER_MODE::COUNT_DOWN:

        // ���݂̎��Ԃ��擾
        nowTime = time(NULL);
        // �o�ߎ��Ԃ��v�Z
        progressTime = nowTime - startTime;

        // �v�������Ԃ�ۑ�
        // �w�肳�ꂽ���Ԃ���o�ߎ��Ԃ��������ƂŃJ�E���g�_�E��
        progressCountTime = countTime - progressTime;

        // �ݒ肳�ꂽ���Ԍo�߂����Ȃ�I����Ԃɂ���
        if (progressCountTime <= 0)
        {
            state = TIMER_STATE::END;
            // 0�ȉ��Ȃ�Ȃ��悤�ɒ���
            progressCountTime = 0;
        }
        break;
    }
}
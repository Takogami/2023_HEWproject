//=============================================================================
//
// �T�E���h���� [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>
#include <vector>

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_FADE = 0,
	SOUND_LABEL_TITLE,
	SOUND_LABEL_STAGE,
	SOUND_LABEL_DORUM,
	SOUND_LABEL_RESULT,
	SOUND_LABEL_DONDON,
	SOUND_LABEL_CLEAR,
	SOUND_LABEL_CURSOR,
	SOUND_LABEL_PRESS,
	SOUND_LABEL_SELECT,
	SOUND_LABEL_BEEP,
	SOUND_LABEL_HIT,
	SOUND_LABEL_HAMMER,
	SOUND_LABEL_BLACK,
	SOUND_LABEL_CLEAN,
	SOUND_LABEL_NOHIT,
	SOUND_LABEL_START,
	SOUND_LABEL_COUNT,
	SOUND_LABEL_END,
	SOUND_LABEL_EVENT,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
HRESULT XA_Initialize(void);

// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
void XA_Release(void);

// �����Ŏw�肵���T�E���h���Đ�����
void XA_Play(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h���~����
void XA_Stop(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
void XA_Resume(SOUND_LABEL label);

#endif

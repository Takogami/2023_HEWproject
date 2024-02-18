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
	SOUND_LABEL_TEST = 0,

	SOUND_LABEL_TITLEBGM,
	SOUND_LABEL_STAGE1_BGM,
	SOUND_LABEL_STAGE2_BGM,
	SOUND_LABEL_STAGE3_BGM,

	SOUND_LABEL_FADEIN,
	SOUND_LABEL_FADEOUT,
	SOUND_LABEL_BOOKSE,
	SOUND_LABEL_GAMEOVER,
	SOUND_LABEL_GAMEOVER_2,
	SOUND_LABEL_DAMAGEHIT,
	SOUND_LABEL_FLY,
	SOUND_LABEL_CURSOR,
	SOUND_LABEL_GAMECLEAR,
	SOUND_LABEL_GAMECLEAR2,
	SOUND_LABEL_PRESS,

	SOUND_LABEL_FALL,
	SOUND_LABEL_GETUP,
	SOUND_LABEL_JUMP,
	SOUND_LABEL_BREAK,
	SOUND_LABEL_DOWN,

	SOUND_LABEL_SCORE_COUNT,
	SOUND_LABEL_CLEAR,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

// �p�����[�^�\����
typedef struct
{
	LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
	bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
} PARAM;

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

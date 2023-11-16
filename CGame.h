#pragma once

/* �C���N���[�h */
#include "CSceneManager.h"

//�Q�[���S�̂�\���N���X
class CGame
{
private:
	
	/* �����o�ϐ� */

	// �Q�[���̍����V�X�e���Q
	// �V���O���g���݌v�ł��邽�߁A�V�X�e�����̃f�[�^���g�p����Ƃ���GetInstance���邱��
	CSceneManager* SceneManager;	// �V�[���}�l�[�W��
	CTextureLoader* TextureLoader;	// �e�N�X�`�����[�_�[
	CTerrainLoader* TerrainLoader;	// �n�`�f�[�^���[�_�[

public:

	/* ���\�b�h */
	CGame();								//����������(�R���X�g���N�^)
	void Update();							//�Q�[�����[�v���Ɏ��s���鏈���������֐�
	~CGame();								//�I������(�f�X�g���N�^)
};

extern CGame* gGame;
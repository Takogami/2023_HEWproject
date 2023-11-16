#pragma once
#include "CSceneManager.h"
#include "CTextureLoader.h"
#include "CTerrainLoader.h"

//�Q�[���S�̂�\���N���X
class CGame
{
public:
	DirectX::XMFLOAT2 cameraPos = { 0, 0 };	//�J�����ʒu

private:
	
	/* �����o�ϐ� */
	CSceneManager* SceneManager;

	CTextureLoader* TextureLoader;
	CTerrainLoader* TerrainLoader;

public:

	/* ���\�b�h */
	CGame();								//����������(�R���X�g���N�^)
	void Update();							//�Q�[�����[�v���Ɏ��s���鏈���������֐�
	~CGame();								//�I������(�f�X�g���N�^)
};

extern CGame* gGame;
#pragma once
#include "CSceneManager.h"
#include "CTextureLoader.h"
#include "CTerrainLoader.h"

//�Q�[���S�̂�\���N���X
class CGame
{
public:
	//�񋓌^
	//��ʂ̏��
	enum SCENE_STATE {
		NO_SCENE,
		TITLE,
		STAGE,
		RESULT,
	};

	//�t�F�[�h���
	enum FADE_STATE {
		NO_FADE,
		FADE_IN,
		FADE_OUT,
	};

	FADE_STATE fadeState = NO_FADE;

	DirectX::XMFLOAT2 cameraPos = { 0, 0 };	//�J�����ʒu

private:

	SCENE_STATE scene = TITLE;		//���݂̉��
	SCENE_STATE newScene = NO_SCENE;

	//�����o�ϐ�
	CSceneManager* SceneManager;

	CTextureLoader* TextureLoader;
	CTerrainLoader* TerrainLoader;

	//�e��ʂ̍X�V�����֐�
	void UpdateTitle();		//�^�C�g�����

public:

	//�����o�֐�
	CGame();								//����������(�R���X�g���N�^)
	void Update();							//�Q�[�����[�v���Ɏ��s���鏈���������֐�
	void SetScene(SCENE_STATE nextScene);	//�V�[���ύX�֐�
	~CGame();								//�I������(�f�X�g���N�^)
};

extern CGame* gGame;
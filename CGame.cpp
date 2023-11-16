#include "CGame.h"
#include "CInput.h"

//�R���X�g���N�^
CGame::CGame()
{
	// TextureLoader�̗B��̃C���X�^���X�𐶐�
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoader�̗B��̃C���X�^���X�𐶐�
	TerrainLoader = CTerrainLoader::GetInstance();

	// �V�[���}�l�[�W���[�̎��̉�
	SceneManager = new CSceneManager;
}

void CGame::Update()
{
	SceneManager->Update();
}


void CGame::SetScene(SCENE_STATE nextScene)
{
	//��ʑJ�ڊJ�n��
	if (newScene != nextScene)
	{
		newScene = nextScene;	//�J�ڐ��ʂ�ۑ�
		fadeState = FADE_OUT;	//�t�F�[�h�A�E�g���J�n
	}
	//�t�F�[�h�A�E�g�I���Ŏ��ۂɃV�[����؂�ւ���
	else
	{
		scene = nextScene;	//��ʂ̐؂�ւ�
		fadeState = FADE_IN;//�؂�ւ����̂Ńt�F�[�h�C���̊J�n

		//�V�[�����Ƃ�BGM�Đ�
		switch (scene)
		{
		case CGame::TITLE:
			break;

		case CGame::STAGE:
			break;

		case CGame::RESULT:
			break;
		}
	}
}

CGame::~CGame()
{
	delete SceneManager;

	TextureLoader->UnloadTexture();
}

void CGame::UpdateTitle()
{
	//��ʓh��Ԃ��Ɛݒ�
	D3D_ClearScreen();

	//��ʍX�V
	D3D_UpdateScreen();
}


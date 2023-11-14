#include "CGame.h"
#include "CInput.h"
#include <XInput.h>

//�R���X�g���N�^
CGame::CGame()
{
	//CTextureLoader�̃V���O���g���𐶐�
	TexLoader = CTextureLoader::GetInstance();
	//�e�N�X�`���ǂݍ���
	TexLoader->LoadTexture();

	//�J�����̍쐬
	Cam = new CCamera;

	//�v���C���[�̎��̉��Ə�����
	player = new CGameObject(vertexBufferCharacter, TexLoader->GetTex(TEX_ID::CHAR1),{0.33f ,0.25f});
	//���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	//�v���C���[�̎��̉��Ə�����
	player2 = new CGameObject(vertexBufferCharacter, TexLoader->GetTex(TEX_ID::TAKO));
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.5f;
	player2->transform.position = { -0.5f, -0.5f };

	//�����̏�����(���ӁFsrand�֐��Ăяo���̓A�v���P�[�V�����J�n����1�񂾂�)
	srand(GetTickCount64());

	//�����V�[���ݒ�
	SetScene(TITLE);

	// CSceneManager�̏�����
	sceneManager = new CSceneManager();
}

void CGame::Update()
{
	// A�{�^���������ꂽ���ǂ������`�F�b�N���ăV�[����؂�ւ���
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_A)) {
		// TITLE��RESULT�̊Ԃ��g�O��
		SetScene((scene == TITLE) ? RESULT : TITLE);
	}

	// ���݂̃V�[�����X�V
	sceneManager->Update();

	//�V�[�����Ƃ�Update�֐������s
	switch (scene)
	{
	case TITLE:
		UpdateTitle();
		break;
	case STAGE:
		break;
	case RESULT:
		break;
	}
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
	//�e�N�X�`���̃A�����[�h
	TexLoader->UnloadTexture();

	delete player;
	delete player2;
	delete Cam;

	SAFE_RELEASE(vertexBufferCharacter);

	// CSceneManager�̉��
	delete sceneManager;
}

void CGame::UpdateTitle()
{
	//��ʓh��Ԃ��Ɛݒ�
	D3D_ClearScreen();

	//�ȉ��Ƃ肠�����J�����ړ��̃e�X�g�p
	static float camPos_x = 0.0f;
	static float camPos_y = 0.0f;
	camPos_x += 0.001f;
	camPos_y += 0.001f;
	Cam->SetCameraPosition(camPos_x, camPos_y);

	//�J�����̍X�V
	Cam->Update();

	//�v���C���[�P�̍X�V
	player->Update();
	player->Draw();

	//�v���C���[�Q�̍X�V(�J�����s�g�p)
	player2->Update();
	player2->Draw();

	//��ʍX�V
	D3D_UpdateScreen();
}

//���ؗp
void CGame::UpdateResult()
{
	//��ʓh��Ԃ��Ɛݒ�
	D3D_ClearScreen();

	//�ȉ��Ƃ肠�����J�����ړ��̃e�X�g�p
	static float camPos_x = 0.0f;
	static float camPos_y = 0.0f;
	camPos_x += 0.001f;
	camPos_y += 0.001f;
	Cam->SetCameraPosition(camPos_x, camPos_y);

	//�J�����̍X�V
	Cam->Update();

	//�v���C���[�P�̍X�V
	player->Update();
	player->Draw();

	

	//��ʍX�V
	D3D_UpdateScreen();
}


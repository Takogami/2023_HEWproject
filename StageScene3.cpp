#include "StageScene3.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h
#include "CGameManager.h"

StageScene3::StageScene3()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �v���C���[�̎��̉��Ə�����
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG3), { 1.0f ,1.0f });
	// �w�i�̐ݒ�
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;

	//	�Q�[���I�u�W�F�N�g�̎��̉��Ə�����
	//	���̂����i�X�^�[�g�j
	ruler[0] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), {1.0f,1.0f});
	ruler[0]->SetUseingCamera(Cam);
	ruler[0]->transform.scale = { 0.3f, 2.5f, 1.0f };
	ruler[0]->transform.position = { -2.0f, 0.0f, 0.3f };
	Objects.push_back(ruler[0]);

	//	���̂����i�S�[���j
	ruler[1] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), { 1.0f,1.0f });
	ruler[1]->SetUseingCamera(Cam);
	ruler[1]->transform.scale = { 0.3f, 2.5f, 1.0f };
	ruler[1]->transform.position = { 18.55f, 0.0f, 0.3f };
	ruler[1]->transform.rotation = 180.0f;
	Objects.push_back(ruler[1]);

	// ��Q��
	pencil = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PENCIL));
	pencil->SetUseingCamera(Cam);
	pencil->transform.scale = { 0.07f, 0.5f, 1.0f };
	pencil->transform.position = { 0.45f, -0.8f, 0.3f };
	pencil->transform.rotation = { 50.0f };
	Objects.push_back(pencil);

	pencil3 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PENCIL));
	pencil3->SetUseingCamera(Cam);
	pencil3->transform.scale = { 0.13f, 0.6f, 1.0f };
	pencil3->transform.position = { 10.98f, -0.525f, 0.3f };
	pencil3->transform.rotation = { 180 };
	Objects.push_back(pencil3);

	// �v���C���[�̎��̉��Ə�����
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player);
	// ���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	// �X�P�[���̐ݒ�
	player->transform * 0.3f;
	player->transform.position.z = -0.1f;
	// �R���C�_�[�̐ݒ�
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.13f, 0.3f };
	player->transform.position.x = -1.5f;
	// �A�j���[�V�����̏�����
	player->InitAnimParameter(true, 5, 10, ANIM_PATTERN::NO_ANIM, 0.2f);

	// �X���[�W���O�̎��̉�
	camSmooth = new CSmoothing;
	camSmooth->InitSmooth(&player->transform.position.x, &Cam->cameraPos.x, 0.1f);

	// �\������X�e�[�W�Ǝg�p����J�����̃|�C���^���w��
	CScene::CreateStage(TERRAIN_ID::STAGE_3, Cam);
}

StageScene3::~StageScene3()
{
	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferCharacter);
	SAFE_RELEASE(vertexBufferObject);

	delete bg;

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
	delete camSmooth;

	// �X�e�[�W�̌�Еt��
	CScene::DestroyStage();
}

void StageScene3::Update()
{
	// �Z���N�g��ʂɖ߂�
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_START) &&
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::START)
	{
		//	�T�E���h�̒�~
		XA_Stop(SOUND_LABEL_FLY);
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT, FADE_TYPE::ERASER);
	}

	// �N���A�A�Q�[���I�[�o�[�ŃV�[���J��
	if (player->GetState() == PState::CLEAR_GAMEOVER && !changeSceneFlg)
	{
		// �N���A�Ȃ�A�V�[���J�ډ��o��ς���
		if (CGameManager::GetInstance()->GetGameState() == GAME_STATE::CLEAR)
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT, FADE_TYPE::ERASER);
		}
		else
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
		}
		changeSceneFlg = true;
	}

	// �e�I�u�W�F�N�g�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	CGameManager::GetInstance()->Update();

	camSmooth->Update();
	// �J�����ړ��̌��E
	if (Cam->cameraPos.x < 0.0f)
	{
		Cam->cameraPos.x = 0.0f;
	}
	if (Cam->cameraPos.x > 16.65f)
	{
		Cam->cameraPos.x = 16.65f;
	}

	Cam->Update();

	CScene::UpdateTerrain();

	// �w�i�Ǐ]
	bg->transform.position.x = Cam->cameraPos.x;

}

void StageScene3::Draw()
{
	// �w�i�̕`��
	bg->Draw();

	// �Q�[���I�[�o�[�̉��o���s���Ă��Ȃ��Ȃ�
	if (CGameManager::GetInstance()->GetGameState() != GAME_STATE::TIME_UP &&
		CGameManager::GetInstance()->GetGameState() != GAME_STATE::ZERO_HP)
	{
		// �n�`�̕`��
		DrawTerrain();
	}
	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	CGameManager::GetInstance()->Draw();
}

#include "StageScene.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h
#include "CGameManager.h"

StageScene::StageScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG), { 1.0f ,1.0f });
	// �w�i�̐ݒ�
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;

	// ��Q��
	zyougi = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER));
	zyougi->SetUseingCamera(Cam);
	zyougi->transform.scale = { 0.3f, 2.3f, 1.0f };
	zyougi->transform.position = { -1.95f, 0.0f, 0.3f };
	Objects.push_back(zyougi);

	// ��Q��
	book = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOOK_OBJ2));
	book->SetUseingCamera(Cam);
	book->transform.scale = { 0.6f, 0.3f, 1.0f };
	book->transform.position = { 0.25f, -0.7f, 0.3f };
	Objects.push_back(book);

	// ��Q��
	pencil = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PENCIL));
	pencil->SetUseingCamera(Cam);
	pencil->transform.scale = { 0.15f, 1.3f, 1.0f };
	pencil->transform.position = { 6.76f, 0.85f, 0.3f };
	Objects.push_back(pencil);

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
	CScene::CreateStage(TERRAIN_ID::STAGE_2, Cam);
}

StageScene::~StageScene()
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

void StageScene::Update()
{
	if (gInput->GetKeyTrigger(VK_DELETE))
	{
		CGameManager::GetInstance()->AddDamage(1);
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
	if (Cam->cameraPos.x < 0.0f)
	{
		Cam->cameraPos.x = 0.0f;
	}
	if (Cam->cameraPos.x > 21.0f)
	{
		Cam->cameraPos.x = 21.0f;
	}

	Cam->Update();

	CScene::UpdateTerrain();

	// �w�i�Ǐ]
	bg->transform.position.x = Cam->cameraPos.x;
}

void StageScene::Draw()
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

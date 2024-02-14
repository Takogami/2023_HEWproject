#include "StageScene4.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h
#include "CGameManager.h"

StageScene4::StageScene4()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �v���C���[�̎��̉��Ə�����
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG), { 1.0f ,1.0f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(bg);
	// �v���C���[�̎��̉��Ə�����
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player);
	// ���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	// �X�P�[���̐ݒ�
	player->transform * 0.2f;
	// �R���C�_�[�̐ݒ�
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.2f, 0.15f };
	// �A�j���[�V�����̏�����
	player->InitAnimParameter(true, 5, 10, ANIM_PATTERN::NO_ANIM, 0.2f);

	player->transform.position.x += 0.5f;
	player->transform.position.y += 0.5f;

	// �w�i�̐ݒ�
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;

	// �X���[�W���O�̎��̉�
	camSmoothX = new CSmoothing;
	camSmoothY = new CSmoothing;
	camSmoothX->InitSmooth(&player->transform.position.x, &Cam->cameraPos.x, 0.1f);
	camSmoothY->InitSmooth(&player->transform.position.y, &Cam->cameraPos.y, 0.1f);

	// ������̐ݒ�
	drawStringTest = new CDrawString;
	drawStringTest->SetFont(FontID::KARAKAZE);
	drawStringTest->SetString("����̓e�X�g�ł��Babc ���������� �A�C�E�G�I ����");
	drawStringTest->SetPosition({ 0.0f, 100.0f });
	drawStringTest->SetFontSize(40.0f);
	drawStringTest->SetFontColor(1.0f, 0.0f, 1.0f);
	drawStringTest->SetFontWeight(FONT_WEIGHT::HEAVY);
	drawStringTest->SetFontStyle(FONT_STYLE::ITALIC);

	drawStringTest2 = new CDrawString;
	drawStringTest2->SetFont(FontID::LETROGO);
	drawStringTest2->SetString("����̓e�X�g�ł��B\nabc\n����������\n�A�C�E�G�I\n����");
	drawStringTest2->SetPosition({ 0.0f, 400.0f });
	drawStringTest2->SetFontSize(30.0f);
	drawStringTest2->SetLineSpacing(20.0f);
	drawStringTest2->SetShadow({ -2.0f, -1.0f }, 0.0f, 0.0f, 0.0f, 0.5f);

	// �\������X�e�[�W�Ǝg�p����J�����̃|�C���^���w��
	CScene::CreateStage(TERRAIN_ID::STAGE_4, Cam);
}

StageScene4::~StageScene4()
{
	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferCharacter);
	SAFE_RELEASE(vertexBufferObject);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
	delete camSmoothX;
	delete camSmoothY;

	delete drawStringTest;
	delete drawStringTest2;

	// �X�e�[�W�̌�Еt��
	CScene::DestroyStage();
}

void StageScene4::Update()
{

	if (gInput->GetKeyTrigger(VK_DELETE))
	{
		CGameManager::GetInstance()->AddDamage(1);
	}

	// �^�C���A�b�v�A�܂���HP��0�ŋ����V�[���J��
	if ((CGameManager::GetInstance()->GetGameState() == GAME_STATE::TIME_UP ||
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::ZERO_HP) && !changeSceneFlg)
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
		changeSceneFlg = true;
	}

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
	}

	// �e�I�u�W�F�N�g�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	UpdateTerrain();
	camSmoothX->Update();
	camSmoothY->Update();
	Cam->Update();

	// �w�i�Ǐ]
	bg->transform.position.x = Cam->cameraPos.x;
}

void StageScene4::Draw()
{
	D3D_ClearScreen();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// �n�`�̕`��
	DrawTerrain();

	CGameManager::GetInstance()->Draw();

	// ������̕`��
	drawStringTest->Draw();
	drawStringTest2->Draw();

	// ��ʍX�V
	D3D_UpdateScreen();
}

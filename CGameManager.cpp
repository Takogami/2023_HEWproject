#include <cstdlib>
#include "CGameManager.h"
#include "CTimer.h"
#include "CGameObject.h"
#include "CTextureLoader.h"
#include "CEase.h"
#include "CDrawString.h"
#include "CSceneManager.h"

// �C���X�^���X�̏�����
CGameManager* CGameManager::instance = nullptr;

CGameManager::CGameManager()
{
	// �^�C�}�[
	gameTime = new CTimer;

	// UI�I�u�W�F�N�g�̎��̉�
	UI_timer = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::TIMER));
	Objects.push_back(UI_timer);
	UI_timer->transform.position = { 1.75f, 0.85f, -0.44f };
	UI_timer->transform.scale = {466.0f * 0.00085f, 517.0f * 0.00085f, 1.0f};
	UI_timer->transform.rotation = -25.0f;

	UI_hpBoard = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::SCORE_BOARD));
	Objects.push_back(UI_hpBoard);
	UI_hpBoard->transform.position = { -1.6f, 0.85f, -0.44f };
	UI_hpBoard->transform.scale = { 1101.0f * 0.0007f, 750.0f * 0.0007f, 1.0f };

	// hp��UI�̎��̉�
	for (int i = 0; i < 3; i++)
	{
		UI_hp[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HEART), {0.333333f, 1.0f});
		Objects.push_back(UI_hp[i]);
		UI_hp[i]->transform.position = { -1.78f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.45f};
		UI_hp[i]->transform.scale = { 286.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };

		breakHeart_R_ease[i] = new CEase;
		UI_breakHeart_R[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HALF_HEART_R));
		Objects.push_back(UI_breakHeart_R[i]);
		UI_breakHeart_R[i]->transform.scale = { 155.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };

		breakHeart_L_ease[i] = new CEase;
		UI_breakHeart_L[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HALF_HEART_L));
		Objects.push_back(UI_breakHeart_L[i]);
		UI_breakHeart_L[i]->transform.scale = { 161.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };
	}

	strTime = new CDrawString;
	strTime->SetFont(FontID::UZURA);
	strTime->SetPosition({ 1355.0f, 65.0f });
	strTime->SetFontSize(100.0f);
	strTime->SetFontColor(1.0f, 0.3f, 0.0f);
	strTime->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	strTime->SetShadow({ -3.0f, -2.0f }, 1.0f, 1.0f, 1.0f, 1.0f);

	strStage = new CDrawString;
	strStage->SetFont(FontID::UZURA);
	strStage->SetString("�X�e�[�W");
	strStage->SetPosition({ 625.0f, 50.0f });
	strStage->SetFontSize(50.0f);
	strStage->SetFontColor(0.0f, 0.0f, 0.0f);
	strStage->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	strStage->SetShadow({ -3.0f, -2.0f }, 1.0f, 0.7f, 0.0f, 1.0f);

	strBg = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	Objects.push_back(strBg);
	strBg->transform.position = { 0.0f, 0.93f, -0.44f };
	strBg->transform.scale = { 772.0f * 0.0013f, 472.0f * 0.0007f, 1.0f };

	stageNum = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::NUM), { 0.1f ,1.0f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(stageNum);
	// �X�P�[���̐ݒ�
	stageNum->transform * 0.18f;
	stageNum->transform.rotation = -10.0f;
	stageNum->transform.position = { 0.285f, 0.93f, -0.45f };

	// ���̉��̌�A���������s��
	this->Init();
}

CGameManager::~CGameManager()
{
	// �^�C�}�[�̉��
	delete gameTime;

	// ������`��̉��
	delete strTime;
	delete strStage;

	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferUI);

	for (int i = 0; i < 3; i++)
	{

	}
	// �e�I�u�W�F�N�g�̉��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}
}

void CGameManager::UpdateUIhp()
{
	// �̗͂�UI�Ǘ�
	if (playerHP <= 5)
	{
		UI_hp[2]->TextureCutout(1, 0);
		// �n�[�t�n�[�g�������Ȃ�s�����ɖ߂�
		if (!heartAlpha_R[2])
		{
			// �����̃n�[�g�̓����x��0��
			UI_breakHeart_R[2]->materialDiffuse.w = 1.0f;
			heartAlpha_R[2] = true;
		}
		// ���łɕs�����Ȃ珙�X�ɓ����ɂ���
		else
		{
			UI_breakHeart_R[2]->materialDiffuse.w =
				UI_breakHeart_R[2]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_R[2]->materialDiffuse.w -= 0.02f : UI_breakHeart_R[2]->materialDiffuse.w;
		}
		// �n�[�g�̃C�[�W���O�̍X�V
		breakHeart_R_ease[2]->Update();
		// ��]����ύX����
		UI_breakHeart_R[2]->transform.rotation =
			UI_breakHeart_R[2]->transform.rotation > -45.0f ?
			UI_breakHeart_R[2]->transform.rotation - 2.0f : UI_breakHeart_R[2]->transform.rotation;
	}
	if (playerHP <= 4)
	{
		UI_hp[2]->TextureCutout(2, 0);
		// �n�[�t�n�[�g�������Ȃ�s�����ɖ߂�
		if (!heartAlpha_L[2])
		{
			// �����̃n�[�g�̓����x��0��
			UI_breakHeart_L[2]->materialDiffuse.w = 1.0f;
			heartAlpha_L[2] = true;
		}
		// ���łɕs�����Ȃ珙�X�ɓ����ɂ���
		else
		{
			UI_breakHeart_L[2]->materialDiffuse.w =
				UI_breakHeart_L[2]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_L[2]->materialDiffuse.w -= 0.02f : UI_breakHeart_L[2]->materialDiffuse.w;
		}
		// �n�[�g�̃C�[�W���O�̍X�V
		breakHeart_L_ease[2]->Update();
		// ��]����ύX����
		UI_breakHeart_L[2]->transform.rotation =
			UI_breakHeart_L[2]->transform.rotation < 45.0f ?
			UI_breakHeart_L[2]->transform.rotation + 2.0f : UI_breakHeart_L[2]->transform.rotation;
	}
	if (playerHP <= 3)
	{
		UI_hp[1]->TextureCutout(1, 0);
		// �n�[�t�n�[�g�������Ȃ�s�����ɖ߂�
		if (!heartAlpha_R[1])
		{
			// �����̃n�[�g�̓����x��0��
			UI_breakHeart_R[1]->materialDiffuse.w = 1.0f;
			heartAlpha_R[1] = true;
		}
		// ���łɕs�����Ȃ珙�X�ɓ����ɂ���
		else
		{
			UI_breakHeart_R[1]->materialDiffuse.w =
				UI_breakHeart_R[1]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_R[1]->materialDiffuse.w -= 0.02f : UI_breakHeart_R[1]->materialDiffuse.w;
		}
		// �n�[�g�̃C�[�W���O�̍X�V
		breakHeart_R_ease[1]->Update();
		// ��]����ύX����
		UI_breakHeart_R[1]->transform.rotation =
			UI_breakHeart_R[1]->transform.rotation > -45.0f ?
			UI_breakHeart_R[1]->transform.rotation - 2.0f : UI_breakHeart_R[1]->transform.rotation;
	}
	if (playerHP <= 2)
	{
		UI_hp[1]->TextureCutout(2, 0);
		// �n�[�t�n�[�g�������Ȃ�s�����ɖ߂�
		if (!heartAlpha_L[1])
		{
			// �����̃n�[�g�̓����x��0��
			UI_breakHeart_L[1]->materialDiffuse.w = 1.0f;
			heartAlpha_L[1] = true;
		}
		// ���łɕs�����Ȃ珙�X�ɓ����ɂ���
		else
		{
			UI_breakHeart_L[1]->materialDiffuse.w =
				UI_breakHeart_L[1]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_L[1]->materialDiffuse.w -= 0.02f : UI_breakHeart_L[1]->materialDiffuse.w;
		}
		// �n�[�g�̃C�[�W���O�̍X�V
		breakHeart_L_ease[1]->Update();
		// ��]����ύX����
		UI_breakHeart_L[1]->transform.rotation =
			UI_breakHeart_L[1]->transform.rotation < 45.0f ?
			UI_breakHeart_L[1]->transform.rotation + 2.0f : UI_breakHeart_L[1]->transform.rotation;
	}
	if (playerHP <= 1)
	{
		UI_hp[0]->TextureCutout(1, 0);
		// �n�[�t�n�[�g�������Ȃ�s�����ɖ߂�
		if (!heartAlpha_R[0])
		{
			// �����̃n�[�g�̓����x��0��
			UI_breakHeart_R[0]->materialDiffuse.w = 1.0f;
			heartAlpha_R[0] = true;
		}
		// ���łɕs�����Ȃ珙�X�ɓ����ɂ���
		else
		{
			UI_breakHeart_R[0]->materialDiffuse.w =
				UI_breakHeart_R[0]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_R[0]->materialDiffuse.w -= 0.02f : UI_breakHeart_R[0]->materialDiffuse.w;
		}
		// �n�[�g�̃C�[�W���O�̍X�V
		breakHeart_R_ease[0]->Update();
		// ��]����ύX����
		UI_breakHeart_R[0]->transform.rotation =
			UI_breakHeart_R[0]->transform.rotation > -45.0f ?
			UI_breakHeart_R[0]->transform.rotation - 2.0f : UI_breakHeart_R[0]->transform.rotation;
	}
	if (playerHP <= 0)
	{
		UI_hp[0]->TextureCutout(2, 0);
		// �n�[�t�n�[�g�������Ȃ�s�����ɖ߂�
		if (!heartAlpha_L[0])
		{
			// �����̃n�[�g�̓����x��0��
			UI_breakHeart_L[0]->materialDiffuse.w = 1.0f;
			heartAlpha_L[0] = true;
		}
		// ���łɕs�����Ȃ珙�X�ɓ����ɂ���
		else
		{
			UI_breakHeart_L[0]->materialDiffuse.w =
				UI_breakHeart_L[0]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_L[0]->materialDiffuse.w -= 0.02f : UI_breakHeart_L[2]->materialDiffuse.w;
		}
		// �n�[�g�̃C�[�W���O�̍X�V
		breakHeart_L_ease[0]->Update();
		// ��]����ύX����
		UI_breakHeart_L[0]->transform.rotation =
			UI_breakHeart_L[0]->transform.rotation < 45.0f ?
			UI_breakHeart_L[0]->transform.rotation + 2.0f : UI_breakHeart_L[0]->transform.rotation;
	}
}

CGameManager* CGameManager::GetInstance()
{
	// �C���X�^���X�����݂��Ă��Ȃ��Ȃ琶������
	if (instance == nullptr)
	{
		instance = new CGameManager;
		// �R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}

	return instance;
}

// �V���O���g���̉������
void CGameManager::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CGameManager::Init()
{
	// �Q�[���̐i�s��Ԃ̃��Z�b�g
	state = GAME_STATE::READY;
	// �X�R�A�̏�����
	score = 0;
	// �^�C�}�[�̏�����
	gameTime->InitTimer(180, TIMER_MODE::COUNT_DOWN);
	nowTime = 180;
	// �v���C���[�̗̑͂�������
	playerHP = PLAYER_HP;

	strTime->SetPosition({ 1355.0f, 65.0f });

	// UI�̏�����
	for (int i = 0; i < 3; i++)
	{
		// �؂蔲���ʒu�����ɖ߂�
		UI_hp[i]->TextureCutout(0, 0);
		// �_���[�W���o�p�̃n�[�t�n�[�g�̏�����
		// �ʒu�̏�����
		UI_breakHeart_L[i]->transform.position = { -1.821f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.47f };
		UI_breakHeart_R[i]->transform.position = { -1.74f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.46f };
		// ��]���̏�����
		UI_breakHeart_L[i]->transform.rotation = 0.0f;
		UI_breakHeart_R[i]->transform.rotation = 0.0f;
		// �����x�̏�����
		UI_breakHeart_L[i]->materialDiffuse.w = 0.0f;
		UI_breakHeart_R[i]->materialDiffuse.w = 0.0f;
		// �C�[�W���O�̏�����
		breakHeart_L_ease[i]->Init(&UI_breakHeart_L[i]->transform.position.y, UI_breakHeart_L[i]->transform.position.y - 0.3f, 0.7f, 0, EASE::easeOutBounce);
		breakHeart_R_ease[i]->Init(&UI_breakHeart_R[i]->transform.position.y, UI_breakHeart_R[i]->transform.position.y - 0.3f, 0.7f, 0, EASE::easeOutBounce);
		// �����t���O�̏�����
		heartAlpha_L[i] = false;
		heartAlpha_R[i] = false;
	}
	soundFlameCounter = 0;
}

void CGameManager::Update()
{
	// �X�e�[�W�ԍ��̐ݒ�
	stageNum->TextureCutout(stageNumber, 0);

	// �^�C�}�[�̍X�V
	gameTime->Update();

	// �̗�UI�̊Ǘ�
	UpdateUIhp();

	// ���ԕ`��p�̈ꎞ�ϐ���錾
	std::string comvartStrTime;	// ������ɕϊ��������Ԃ��i�[
	int digit_rank;				// ���݂̎��Ԃ̌������i�[

	// �Q�[���̐i�s�󋵂ɉ����čX�V������ύX
	switch (state)
	{
	case GAME_STATE::READY:
		// �t�F�[�h���I�����Ă���^�C�}�[���J�n����
		if (CSceneManager::GetInstance()->GetFadeState() == FADE_STATE::NO_FADE)
		{
			// �^�C�}�[�̊J�n
			gameTime->StartTimer();
			// �Q�[���X�e�[�g�̕ύX
			state = GAME_STATE::START;
		}
		// ���Ԃ𕶎���^�ɕϊ�
		comvartStrTime = std::to_string(nowTime);
		// ���Ԃ̕�������Z�b�g
		strTime->SetString(comvartStrTime);
		break;

	case GAME_STATE::START:
		// �v���C���[��HP��0�Ȃ�
		if (playerHP <= 0)
		{
			//	�T�E���h��~
			XA_Stop(SOUND_LABEL_STAGE1_BGM);
			XA_Stop(SOUND_LABEL_STAGE2_BGM);
			XA_Stop(SOUND_LABEL_STAGE3_BGM);
			XA_Stop(SOUND_LABEL_FLY);
			//�T�E���h�Đ�
			XA_Play(SOUND_LABEL_DOWN);
			// ��Ԃ�HP0��
			state = GAME_STATE::ZERO_HP;
		}
		// �^�C����0�ɂȂ����Ȃ�
		else if (gameTime->GetTimerState() == TIMER_STATE::END)
		{
			// ��Ԃ��^�C���A�b�v��
			state = GAME_STATE::TIME_UP;
			//	�T�E���h��~
			XA_Stop(SOUND_LABEL_STAGE1_BGM);
			XA_Stop(SOUND_LABEL_STAGE2_BGM);
			XA_Stop(SOUND_LABEL_STAGE3_BGM);
			XA_Stop(SOUND_LABEL_FLY);
			//�T�E���h�Đ�
			XA_Play(SOUND_LABEL_DOWN);
		}
		// ���݂̃Q�[�����Ԃ��󂯎��
		nowTime = (int)gameTime->GetTime();
		// ���Ԃ𕶎���^�ɕϊ�
		comvartStrTime = std::to_string(nowTime);
		// ���Ԃ̕�������Z�b�g
		strTime->SetString(comvartStrTime);
		// ������̒������猅�����擾
		digit_rank = comvartStrTime.length();
		// �����ɉ����ĕ\���ʒu��ύX����
		if (digit_rank <= 2)
		{
			strTime->SetPosition({ 1355.0f + (50 / digit_rank), 65.0f });
		}
		break;

	case GAME_STATE::TIME_UP:
		// �t���[�����J�E���g
		soundFlameCounter++;
		// 170�t���[��
		if (soundFlameCounter == 170)
		{
			//�|���T�E���h�Đ�
			XA_Play(SOUND_LABEL_GETUP);
		}
		// 200�t���[��
		if (soundFlameCounter == 200)
		{
			XA_Play(SOUND_LABEL_GAMEOVER_2);
		}
		break;

	case GAME_STATE::ZERO_HP:
		// �t���[�����J�E���g
		soundFlameCounter++;
		// 170�t���[��
		if (soundFlameCounter == 170)
		{
			//�|���T�E���h�Đ�
			XA_Play(SOUND_LABEL_GETUP);
		}
		// 200�t���[��
		if (soundFlameCounter == 200)
		{
			XA_Play(SOUND_LABEL_GAMEOVER_2);
		}
		break;

	case GAME_STATE::CLEAR:
		// �^�C�}�[�̃X�g�b�v����
		gameTime->PauseTimer();
		break;

	default:
		break;
	}

	// �Q�[���֘AUI�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void CGameManager::Draw()
{
	// �Q�[���֘AUI�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// �����̕`��
	strTime->Draw();
	strStage->Draw();
}

void CGameManager::AddScore(int addScore)
{
	score += addScore;
}

void CGameManager::AddDamage(int addDamage)
{
	// �l��1~6�ŃN�����v
	addDamage = addDamage < 1 ? 1 : addDamage;
	addDamage = addDamage > 6 ? 6 : addDamage;

	// �v���C���[��HP����_���[�W������
	playerHP -= addDamage;
	// 0�ȉ��ɂȂ�Ȃ��悤�ɒ���
	playerHP = playerHP < 0 ? 0 : playerHP;
}

GAME_STATE CGameManager::GetGameState()
{
	return state;
}

int CGameManager::GetClearTime()
{
	// �^�C�}�[����~���Ă��Ȃ��Ȃ�A�N���A���Ă��Ȃ��Ƃ݂Ȃ�0��Ԃ�
	if (gameTime->GetTimerState() != TIMER_STATE::PAUSE)
	{
		return 0;
	}

	// �o�ߎ��Ԃ�Ԃ�
	return (int)gameTime->GetProgressTime();
}

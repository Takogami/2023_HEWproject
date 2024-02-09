#include "ResultScene.h"
#include "CSceneManager.h"

ResultScene::ResultScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	GameOverObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER));
	Objects.push_back(GameOverObj);
	GameOverObj->transform.position = { -0.5f, 0.0f, 0.5f };
	GameOverObj->transform.scale = { 512.0f * 0.0045f, 512.0f * 0.0045f, 1.0f };

	// �J�[�\���̎��̉��Ə�����
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.position = { 0.524f, 0.2f };
	cursor->transform.rotation = -30.0f;
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });

	retry = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(retry);
	retry->transform * 0.5f;
	retry->transform.position = { 0.9f, 0.2f };

	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToSelect);
	goToSelect->transform * 0.5f;
	goToSelect->transform.position = { 0.9f, -0.1f };

	goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToTitle);
	goToTitle->transform * 0.5f;
	goToTitle->transform.position = { 0.9f, -0.4f };
}

ResultScene::~ResultScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
}

void ResultScene::SetPrevStage(int prev)
{
	prevScene = prev;
}


void ResultScene::Update()
{
	// ���ʂɉ����čX�V������ς���
	switch (state)
	{
	case RESULT_STATE::GAMEOVER:
		// �Q�[���I�[�o�[��ʂ̍X�V
		UpdateGameOver();
		break;

	case RESULT_STATE::CLEAR:
		// �N���A��ʂ̍X�V
		UpdateClear();
		break;

	default:

		break;
	}

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void ResultScene::UpdateClear()
{
}

void ResultScene::UpdateGameOver()
{
	// �O��̃V�[�����烊�g���C�œǂݍ��ރV�[��������
	// int�^�Őݒ肳�ꂽ���̂�SCENE_ID�^�ɕϊ�����
	SCENE_ID loadScene = (SCENE_ID)prevScene;

	// �J�[�\���̓��͏��������s
	cursor->CursorInput();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// CCursor�ł̗񋓌^��Scene���擾����
		cursorPoint = (CCursor_PointResult)cursor->GetCursorPoint();

		// �J�[�\���̃|�C���g�ʒu�őJ�ڐ�̃V�[����ύX
		switch (cursorPoint)
		{
		case CCursor_PointResult::RETRY:	// �R���e�B�j���[
			// �O��̃X�e�[�W�ɑJ�ڂ���
			switch (loadScene)
			{
			case SCENE_ID::STAGE_1:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
				break;

			case SCENE_ID::STAGE_2:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2);
				break;

			default:
				break;
			}
			break;

		case CCursor_PointResult::SELECT:	// �Z���N�g�ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			break;

		case CCursor_PointResult::TITLE:	// �^�C�g���ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
			break;

		default:
			break;
		}
	}
}

void ResultScene::Draw()
{
	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}
}

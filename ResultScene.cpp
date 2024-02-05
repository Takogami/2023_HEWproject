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

	//�v���C���[�̎��̉��Ə�����
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(cursor);
	cursor->transform * 0.15f;
	cursor->transform.position = { 0.524f, -0.3f };

	//�v���C���[�̎��̉��Ə�����
	retry = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(retry);
	retry->transform * 0.5f;
	retry->transform.position = { 0.9f, -0.3f };

	//�v���C���[�̎��̉��Ə�����
	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToSelect);
	goToSelect->transform * 0.5f;
	goToSelect->transform.position = { 0.9f, -0.6f };

	//�v���C���[�̎��̉��Ə�����
	goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToTitle);
	goToTitle->transform * 0.5f;
	goToTitle->transform.position = { 0.9f, -0.9f };
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
	// �O��̃V�[�����烊�g���C�œǂݍ��ރV�[��������
	// int�^�Őݒ肳�ꂽ���̂�SCENE_ID�^�ɕϊ�����
	SCENE_ID loadScene = (SCENE_ID)prevScene;

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// CCursor�ł̗񋓌^��Scene���擾����
		cursorPoint = (CCursor_PointResult)cursor->GetCursorPoint();

		// �J�[�\���̃|�C���g�ʒu�őJ�ڐ�̃V�[����ύX
		switch (cursorPoint)
		{
		case CCursor_PointResult::RETRY:	// ���g���C
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

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void ResultScene::Draw()
{
	D3D_ClearScreen();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// ��ʍX�V
	D3D_UpdateScreen();
}

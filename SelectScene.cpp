#include "SelectScene.h"

SelectScene::SelectScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;
}

SelectScene::~SelectScene()
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

void SelectScene::Update()
{
}

void SelectScene::Draw()
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

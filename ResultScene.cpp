#include "ResultScene.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	// �e�N���X�̃f�X�g���N�^�𖾎��I�ɌĂяo��
	CScene::~CScene();
}

void ResultScene::Update()
{
}

void ResultScene::Draw()
{
	D3D_ClearScreen();
	//��ʍX�V
	D3D_UpdateScreen();
}

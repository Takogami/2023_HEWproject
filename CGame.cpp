/* �C���N���[�h */
#include "CGame.h"
#include "xa2.h"

//�R���X�g���N�^
CGame::CGame()
{
	// TextureLoader�̗B��̃C���X�^���X�𐶐�
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoader�̗B��̃C���X�^���X�𐶐�
	TerrainLoader = CTerrainLoader::GetInstance();

	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�T�E���h�ǂݍ��݂Ɏ��s", "�G���[", MB_OK | MB_ICONERROR);
	}

	// SceneManager�̗B��̃C���X�^���X�𐶐�
	SceneManager = CSceneManager::GetInstance();
}

void CGame::Update()
{
	SceneManager->Update();

	// escape�L�[�ŃQ�[�����I��
	if (gInput->GetKeyPress(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

CGame::~CGame()
{
	TextureLoader->UnloadTexture();
	XA_Release();
}


#pragma once

#include "TitleScene.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "StageScene3.h"
#include "StageScene4.h"
#include "SelectScene.h"
#include "ResultScene.h"

//	�V�[���̎�ށi�񋓌^�j
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	RESULT,
};

enum class FADE_STATE
{
	NO_FADE,
	FADE_IN,
	FADE_OUT,
};

class CSceneManager
{
private:
	// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^
	static CSceneManager* instance;

	TitleScene* title = nullptr;			//�^�C�g���V�[���N���X
	StageScene* stage1 = nullptr;			//�X�e�[�W�V�[��1�N���X
	StageScene2* stage2 = nullptr;			//�X�e�[�W�V�[��2�N���X
	StageScene3* stage3 = nullptr;			//�X�e�[�W�V�[��3�N���X
	StageScene4* stage4 = nullptr;			//�X�e�[�W�V�[��4�N���X
	SelectScene* select = nullptr;			//�Z���N�g�V�[���N���X
	ResultScene* result = nullptr;			//���U���g�V�[���N���X

	CGameManager* gameManager;

	CGameObject* fade;
	ID3D11Buffer* vertexBuffer;

	SCENE_ID NowScene = SCENE_ID::TITLE;
	SCENE_ID NewScene = SCENE_ID::TITLE;
	SCENE_ID retryLoadScene = SCENE_ID::TITLE;

	// �O��̃Q�[���̃N���A�^�C��
	int prevGameClearTime = 0;

	FADE_STATE fadeState = FADE_STATE::NO_FADE;

	CSceneManager();
	~CSceneManager();
	// �A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();

public:
	// �C���X�^���X���擾���邽�߂̃��\�b�h
	static CSceneManager* GetInstance();

	void Update();							//�V�[���̊Ǘ�
	void ChangeScene(SCENE_ID _inScene);	//�V�[���̕ύX

	FADE_STATE GetFadeState() { return fadeState; }
};


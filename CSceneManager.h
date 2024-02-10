#pragma once

#include "TitleScene.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "SelectScene.h"
#include "ResultScene.h"

// �V�[���̎�ށi�񋓌^�j
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_1,
	STAGE_2,
	RESULT,
};

// �t�F�[�h���
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

	TitleScene* title = nullptr;			//�^�C�g���V�[��
	StageScene* stage1 = nullptr;			//�X�e�[�W�V�[��1
	StageScene2* stage2 = nullptr;			//�X�e�[�W�V�[��2
	SelectScene* select = nullptr;			//�Z���N�g�V�[��
	ResultScene* result = nullptr;			//���U���g�V�[��

	// �t�F�[�h�p
	CGameObject* fade;
	ID3D11Buffer* vertexBuffer;

	CGameManager* GameManager;

	SCENE_ID NowScene = SCENE_ID::TITLE;		// ���݂̃V�[���̏��
	SCENE_ID NewScene = SCENE_ID::TITLE;		// �V�����̃V�[��
	SCENE_ID retryLoadScene = SCENE_ID::TITLE;	// ���g���C���ɓǂݍ��ރV�[��

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

	// �t�F�[�h�X�e�[�g��Ԃ�
	FADE_STATE GetFadeState() { return fadeState; }
};


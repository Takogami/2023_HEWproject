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

enum class FADE_TYPE
{
	NORMAL,	// �ʏ�t�F�[�h
	ERASER,	// �����S���t�F�[�h
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

	CGameObject* fade;					// �ʏ�t�F�[�h�p�|���S��
	CGameObject* fade_eraser;			// �����S���t�F�[�h�p�|���S��
	int fade_eraser_counter = 0;		// �����S���̃t�F�[�h���Ԃ��v��
	const int fade_eraser_flame = 80;	// �����S���̃t�F�[�h�ɂ����鎞��

	ID3D11Buffer* vertexBuffer;

	SCENE_ID NowScene = SCENE_ID::TITLE;
	SCENE_ID NewScene = SCENE_ID::TITLE;
	SCENE_ID retryLoadScene = SCENE_ID::TITLE;

	FADE_STATE fadeState = FADE_STATE::NO_FADE;
	FADE_TYPE fadeType = FADE_TYPE::NORMAL;

	CSceneManager();
	~CSceneManager();
	// �A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();

public:
	// �C���X�^���X���擾���邽�߂̃��\�b�h
	static CSceneManager* GetInstance();

	void Update();							//�V�[���̊Ǘ�
	void ChangeScene(SCENE_ID _inScene, FADE_TYPE fadeType = FADE_TYPE::NORMAL);	//�V�[���̕ύX

	FADE_STATE GetFadeState() { return fadeState; }
};


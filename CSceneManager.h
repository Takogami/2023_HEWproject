#pragma once

#include "TitleScene.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "SelectScene.h"
#include "ResultScene.h"

//	�V�[���̎�ށi�񋓌^�j
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_1,
	STAGE_2,
	RESULT,
};

class CSceneManager
{
private:
	// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^
	static CSceneManager* instance;

	TitleScene* title = nullptr;			//�^�C�g���V�[���N���X
	StageScene* stage1 = nullptr;			//�X�e�[�W�V�[��1�N���X
	StageScene2* stage2 = nullptr;			//�X�e�[�W�V�[��2�N���X
	SelectScene* select = nullptr;			//�Z���N�g�V�[���N���X
	ResultScene* result = nullptr;			//���U���g�V�[���N���X

	CEventManager* eventManager;

	std::list<CScene*> scenes;

	SCENE_ID NowScene = SCENE_ID::TITLE;	//���݂̃V�[���̏��

	CSceneManager();
	~CSceneManager();
	// �A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();

public:
	// �C���X�^���X���擾���邽�߂̃��\�b�h
	static CSceneManager* GetInstance();

	void Update();							//�V�[���̊Ǘ�
	void ChangeScene(SCENE_ID _inScene);	//�V�[���̕ύX
};


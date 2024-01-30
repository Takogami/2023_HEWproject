#pragma once

#include "TitleScene.h"
#include "ResultScene.h"
#include "StageScene.h"
#include "SelectScene.h"

//	�V�[���̎�ށi�񋓌^�j
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_01,
	RESULT,
};

class CSceneManager
{
private:
	// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^
	static CSceneManager* instance;

	TitleScene* title;						//�^�C�g���V�[���N���X
	StageScene* stage;						//�X�e�[�W�V�[���N���X
	ResultScene* result;					//���U���g�V�[���N���X
	SelectScene* select;

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


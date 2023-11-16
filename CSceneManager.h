#pragma once

#include "TitleScene.h"
#include "ResultScene.h"

//	�V�[���̎�ށi�񋓌^�j
enum class SCENE_ID
{
	TITLE,
	STAGE_01,
	RESULT,
};

class CSceneManager
{
private:

	TitleScene* title;						//�^�C�g���V�[���N���X
	ResultScene* result;					//���U���g�V�[���N���X

	SCENE_ID NowScene = SCENE_ID::RESULT;	//���݂̃V�[���̏��

public:

	CSceneManager();
	~CSceneManager();

	void Update();							//�V�[���̊Ǘ�
	void ChangeScene(SCENE_ID _inScene);	//�V�[���̕ύX
};


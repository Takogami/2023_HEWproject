#pragma once
#include "CTerrainLoader.h"
#include "TitleScene.h"
#include "ResultScene.h"

//	�V�[���̎�ށi�񋓌^�j
enum class SCENE_LIST
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

	SCENE_LIST NowScene = SCENE_LIST::RESULT;	//���݂̃V�[���̏��

public:

	CSceneManager();
	~CSceneManager();

	void Update();							//�V�[���̊Ǘ�
	void ChangeScene(SCENE_LIST _inScene);	//�V�[���̕ύX
};


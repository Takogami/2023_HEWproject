#pragma 
#include"TitleScene.h"
#include"ResultScene.h"

//	�V�[���̎�ށi�񋓌^�j

enum class SceneList
{
	TITLE,
	STAGE_01,
	RESULT
};

class CSceneManager
{
private:
	

	SceneList NowScene;	//���݂̃V�[���̏��

	TitleScene* titleS;
	ResultScene* resultS;

	bool exit = false;				//�I���t���O

public:

	CSceneManager();
	~CSceneManager();

	void Update();				//�V�[���̊Ǘ�
	void ChangeScene(SceneList _inScene);	//�V�[���̕ύX
	void Exit();

};


#pragma once
#include "CScene.h"
class StageScene :
    public CScene
{
private:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	CGameObject* player;

	ID3D11Buffer* vertexBufferCharacter;

	// �V�[���J�ڒ������肷��t���O
	bool changeSceneFlg = false;

public:
	StageScene();
	~StageScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;

};


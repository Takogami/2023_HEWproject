#pragma once
#include "CScene.h"
#include"CSmoothing.h"

class StageScene :
    public CScene
{
private:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	// �w�i
	CGameObject* bg;

	CPlayer* player;

	// �V�[���J�ڒ������肷��t���O
	bool changeSceneFlg = false;

	// �J�����Ǐ]�̃X���[�W���O
	CSmoothing* camSmooth;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

public:
	StageScene();
	~StageScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;

};


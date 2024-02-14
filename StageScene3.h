#pragma once
#include "CScene.h"
#include"CSmoothing.h"

class StageScene3 :
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

	bool changeSceneFlg = false;

	// �J�����Ǐ]�̃X���[�W���O
	CSmoothing* camSmoothX;
	CSmoothing* camSmoothY;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

	CDrawString* drawStringTest;
	CDrawString* drawStringTest2;

public:
	StageScene3();
	~StageScene3();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


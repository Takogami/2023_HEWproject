#pragma once

/* �C���N���[�h */
#include"CScene.h"
#include"CSmoothing.h"

class StageScene2 : public CScene
{
private:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	// �w�i
	CGameObject* bg;

	CPlayer* player;

	// �J�����Ǐ]�̃X���[�W���O
	CSmoothing* camSmooth;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

	CDrawString* drawStringTest;
	CDrawString* drawStringTest2;

public:
	StageScene2();
	~StageScene2();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


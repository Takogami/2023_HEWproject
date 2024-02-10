#pragma once
#include "CScene.h"

class Stage2Scene :
    public CScene
{
private:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	CPlayer* player;

	ID3D11Buffer* vertexBufferCharacter;

public:
	Stage2Scene();
	~Stage2Scene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;

};


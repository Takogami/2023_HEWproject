#pragma once

/* �C���N���[�h */
#include"CScene.h"

class ResultScene : public CScene
{
private:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	CPlayer* player;

	ID3D11Buffer* vertexBufferCharacter;

public:
	ResultScene();
	~ResultScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


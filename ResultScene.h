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

	/* �� ���݃v���C���[ �� */
	CGameObject* player;
	float dirX = 0.0f;
	float dirY = 0.0f;
	/* �� ���݃v���C���[ �� */

	ID3D11Buffer* vertexBufferCharacter;

public:
	ResultScene();
	~ResultScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


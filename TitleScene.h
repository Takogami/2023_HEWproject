#pragma once

/* �C���N���[�h */
#include"CScene.h"

// CTitleScene�N���X
class TitleScene : public CScene
{
private:
	// �^�C�g���V�[���̃J����
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	CGameObject* player;
	CGameObject* player2;

	ID3D11Buffer* vertexBufferCharacter;

public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene() override;

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};



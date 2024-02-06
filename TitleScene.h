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

	CCursor* cursor;
	CGameObject* goToSelect;
	CGameObject* goToOption;
	CGameObject* exitGame;
	CGameObject* bg;
	CGameObject* Title;

	// �^�C�g���̃C�[�W���O
	CEase* titleEase;
	bool TitleEaseFg = false;

	ID3D11Buffer* vertexBufferObject;

	CCursor_Point cursorPoint = CCursor_Point::STAGE;

public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene() override;

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};



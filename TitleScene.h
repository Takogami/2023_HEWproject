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

	// �I�u�W�F�N�g
	CCursor* cursor;
	CGameObject* goToSelect;
	CGameObject* goToOption;
	CGameObject* exitGame;
	CGameObject* bg;
	CGameObject* Title;
	CGameObject* ruler;
	CGameObject* ruler2;

	// �^�C�g�����o�p
	CGameObject* enemyObj;
	CGameObject* enemyObj_reverse;
	CGameObject* playerObj;
	// ���o�p�̓G�����̕����̈ړ����I���������Ǘ�����t���O
	bool moveDirNegative = false;
	// ���o�p�̓G�����̕����̈ړ����I���������Ǘ�����t���O
	bool moveDirPositive = false;
	// �G�̈ړ��C�[�W���O
	CEase* enemyEase;
	CEase* enemyEaseR;
	CEase* playerFlyEase;

	// �I���̃C�[�W���O
	CEase* selectEaseX;
	CEase* selectEaseY;

	// �I���{�^���������ꂽ���ǂ����𔻒肷��t���O
	bool selectFlg = false;
	// �I�����ꂽ�Ƃ��̃C�[�W���O���������Ă��邩���肷��t���O
	bool selectEnd = false;

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
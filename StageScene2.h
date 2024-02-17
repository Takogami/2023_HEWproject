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

	CGameObject* zyougi;
	CGameObject* zyougi2;
	CGameObject* zyougi3;
	CGameObject* book;
	CGameObject* book2;
	CGameObject* book3;
	CGameObject* book4;
	CGameObject* book5;
	CGameObject* pencil;
	CGameObject* pencil2;
	CGameObject* pencil3;

	CPlayer* player;

	// �V�[���J�ڒ������肷��t���O
	bool changeSceneFlg = false;

	// �J�����Ǐ]�̃X���[�W���O
	CSmoothing* camSmooth;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

public:
	StageScene2();
	~StageScene2();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


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

	CGameObject* zyougi;
	CGameObject* zyougi2;
	CGameObject* book;
	CGameObject* book2;
	CGameObject* pencil2;
	CGameObject* eraser;
	CGameObject* pencil;
	CGameObject* kanban1;
	CGameObject* kanban2;
	CGameObject* kanban3;
	CGameObject* kanban4;
	CGameObject* kanban5;

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


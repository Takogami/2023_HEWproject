#pragma once
#include "CScene.h"

// ���U���g��ʂ̏��
enum class RESULT_STATE
{
	GAMEOVER,
	CLEAR,
};

class ResultScene :
    public CScene
{
private:

	CCursor* cursor;
	CGameObject* retry;
	CGameObject* goToSelect;
	CGameObject* goToTitle;

	CCursor_PointResult cursorPoint = CCursor_PointResult::RETRY;

public:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	// �I�u�W�F�N�g�̕`��
	ID3D11Buffer* vertexBufferObject;

	// �X�e�[�W�̃v���r���[
	CGameObject* GameOverObj;

	// ���U���g�J�ڑO�̃X�e�[�W������������
	int prevScene = 0;

public:
	ResultScene();
	~ResultScene() override;

	// ���U���g�J�ڑO�̃X�e�[�W�̐ݒ�
	// ��SCENE_ID�^�����݃C���N���[�h�Ŏg���Ȃ�����int�^�Ŏw�肵�Ă�������
	void SetPrevStage(int prev);

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


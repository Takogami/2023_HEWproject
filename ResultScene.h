#pragma once
#include "CScene.h"

// ���U���g��ʂ̏��
enum class RESULT_STATE
{
	GAMEOVER,
	CLEAR,
};

enum class RESULT_SELECT
{
	CONTINUE = 1,	//	�R���e�j���[
	TITLE,			//	�^�C�g���V�[��
};

class ResultScene :
    public CScene
{
private:

	CCursor* cursor;
	CGameObject* retry;
	CGameObject* goToSelect;
	CGameObject* goToTitle;

	CCursor_PointResult cursorPoint;

public:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	// �I�u�W�F�N�g�̕`��
	ID3D11Buffer* vertexBufferObject;

	// �I�𒆂̃X�e�[�W�ԍ�
	int stageNum = 1;
	// �I�𒆂̃X�e�[�W
	RESULT_SELECT userSelect = RESULT_SELECT::CONTINUE;

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


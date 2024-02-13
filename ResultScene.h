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

	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	// �I�u�W�F�N�g�̕`��
	ID3D11Buffer* vertexBufferObject;

	/*---------------�Q�[���I�[�o�[��ʂ̃I�u�W�F�N�g-----------------------*/
	CCursor* cursor;
	CGameObject* bg;
	CGameObject* retry;
	CGameObject* goToSelect;
	CGameObject* goToTitle;
	CGameObject* GameOverObj;
	CGameObject* GameOverString;
	/*---------------�Q�[���I�[�o�[��ʂ̃I�u�W�F�N�g-----------------------*/

	/*-------------------�N���A��ʂ̃I�u�W�F�N�g---------------------------*/
	CCursor* c_cursor;
	CGameObject* c_bg;
	CGameObject* c_goToSelect;
	CGameObject* c_goToTitle;
	CGameObject* clearString;
	CGameObject* scoreBoard;
	/*-------------------�N���A��ʂ̃I�u�W�F�N�g---------------------------*/

	// ���U���g�J�ڑO�̃X�e�[�W������������
	int prevScene = 0;

	CCursor_PointResult cursorPoint = CCursor_PointResult::RETRY;
	CCursor_PointClear c_cursorPoint = CCursor_PointClear::SELECT;

	// �Q�[���I�[�o�[�ł��邩�N���A�ł��邩������
	RESULT_STATE state = RESULT_STATE::CLEAR;

	// �I���̃C�[�W���O
	CEase* selectEaseX;
	CEase* selectEaseY;

	CEase* gameOverObjEaseX;
	CEase* gameOverObjEaseY;
	// �Q�[���I�[�o�[�����̃C�[�W���O
	CEase* gameOverEase;

	CEase* clearStringEaseX;
	CEase* clearStringEaseY;

	// �I���{�^���������ꂽ���ǂ����𔻒肷��t���O
	bool selectFlg = false;
	// �I�����ꂽ�Ƃ��̃C�[�W���O���������Ă��邩���肷��t���O
	bool selectEnd = false;

	// �N���A��ʂ̍X�V
	void UpdateClear();
	// �Q�[���I�[�o�[��ʂ̍X�V
	void UpdateGameOver();

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


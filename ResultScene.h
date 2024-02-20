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
	CGameObject* enemyObj;
	CGameObject* enemyObj2;
	CGameObject* ClearTime;
	CGameObject* cTime;
	/*-------------------�N���A��ʂ̃I�u�W�F�N�g---------------------------*/

	// ���U���g�J�ڑO�̃X�e�[�W������������
	int prevScene = 0;

	CCursor_PointResult cursorPoint = CCursor_PointResult::RETRY;
	CCursor_PointClear c_cursorPoint = CCursor_PointClear::SELECT;

	// �Q�[���I�[�o�[�ł��邩�N���A�ł��邩������
	RESULT_STATE state = RESULT_STATE::GAMEOVER;

	// �I���̃C�[�W���O
	CEase* selectEaseX;
	CEase* selectEaseY;

	CEase* gameOverObjEaseX;
	CEase* gameOverObjEaseY;
	// �Q�[���I�[�o�[�����̃C�[�W���O
	CEase* gameOverEase;

	// �N���A�����̃C�[�W���O
	CEase* clearStringEaseX;
	CEase* clearStringEaseY;

	// �X�R�A�{�[�h�~���̃C�[�W���O
	CEase* scoreBoardEase;

	// �G�o���̃C�[�W���O
	CEase* enemyEase;
	CEase* enemyEase2;
	// �G�̓����̃C�[�W���O
	CEase* enemyHappyEase;
	bool enemyHappyEaseFlg = false;
	CEase* enemyHappyEase2;
	bool enemyHappyEaseFlg2 = false;
	// �G�̃W�����v�����������𔻒�
	bool endJumpEnemy = false;

	// �Z���N�g�\�ɂ��邩�ǂ����̃t���O
	bool selectOK = false;
	// �I���{�^���������ꂽ���ǂ����𔻒肷��t���O
	bool selectFlg = false;
	// �I�����ꂽ�Ƃ��̃C�[�W���O���������Ă��邩���肷��t���O
	bool selectEnd = false;

	// �N���A�^�C���̕`��
	/*CDrawString* strClearTime;
	CDrawString* strClearTimeNum;
	CDrawString* strSecond;*/

	// �󂯎�����N���A�^�C����ۑ�
	int clearTime = 0;
	// �N���A���Ԃ̃J�E���g
	int clearTimeCount = 0;
	// SE���Đ����ꂽ���ǂ����̃t���O
	bool sePlayFlg = false;
	// SE���Đ�����܂ł̒x����v��
	int seFlameCounter = 0;

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
	// �N���A�^�C����ݒ肷��
	void SetClearTime(int gameClearTime) { clearTime = gameClearTime; }
	// �ǂ���̃��U���g�Ɉڍs���邩��ݒ肷��
	void SetResultState(RESULT_STATE rState) { state = rState; }

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


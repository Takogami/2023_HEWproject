#pragma once
#include "CScene.h"


enum class SELECT_NUM
{
	CONTINUE = 1,	//	�R���e�j���[
	TITLE,		//	�^�C�g���V�[��
};


class CGameOverScene :
    public CScene
{
private:


public:
	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

	// �I�u�W�F�N�g�̕`��
	ID3D11Buffer* vertexBufferObject;

	// �I���𑣂�����
	CDrawString* StageSelect;

	// �I�𒆂̃X�e�[�W�ԍ�
	int stageNum = 1;
	// �I�𒆂̃X�e�[�W
	SELECT_NUM userSelect = SELECT_NUM::CONTINUE;

	// �X�e�[�W�̃v���r���[
	CGameObject* StagePreview;

	// �X�e�[�W�̑I���I�u�W�F�N�g�̃��X�g
	std::vector<CGameObject*> StageList;
	// �X�e�[�W���X�g�̐�
	const int listNum = 2;
	// �����̏I���ʒu
	std::vector<float> moveEndPos;
	// �����̊J�n�Ǘ��t���O
	bool selectMoveUp = false;
	bool selectMoveDown = false;
	// �X�e�[�W�I���̃C�[�W���O
	std::vector<CEase*> selectEase;


public:
	CGameOverScene();
	~CGameOverScene() override;

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


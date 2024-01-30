#pragma once
#include "CScene.h"

// �X�e�[�W����
enum class STAGE_NUM
{
	STAGE1 = 1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
};

class SelectScene :
    public CScene
{
private:
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
	STAGE_NUM userSelect = STAGE_NUM::STAGE1;

	// �X�e�[�W�̃v���r���[
	CGameObject* StagePreview;
	CGameObject* StagePreview2;

	// �X�e�[�W�̑I���I�u�W�F�N�g�̃��X�g
	std::vector<CGameObject*>StageList;
	// �X�e�[�W���X�g�̐�
	const int listNum = 5;
	// �����̏I���ʒu
	std::vector<float> moveEndPos;
	// �����̊J�n�Ǘ��t���O
	bool selectMoveUp = false;
	bool selectMoveDown = false;
	// �X�e�[�W�I���̃C�[�W���O
	std::vector<CEase*> selectEase;


public:
	SelectScene();
	~SelectScene() override;

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};

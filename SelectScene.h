#pragma once
#include "CScene.h"
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

	// �\������X�e�[�W�̖��O
	CDrawString* StageName;
	// �I���𑣂�����
	CDrawString* StageSelect;

public:
	SelectScene();
	~SelectScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};


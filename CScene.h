#pragma once

#include "CGameObject.h"
#include "CCamera.h"

class CScene
{
private:


public:

	/* ���\�b�h */

	// �R���X�g���N�^
	CScene();
	// �f�X�X�g���N�^
	virtual ~CScene();

	// �I�[�o�[���C�h����p�̊֐�
	// �V�[���̍X�V����
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
};


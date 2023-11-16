#pragma once

/* �C���N���[�h */
#include <list>
#include "CGameObject.h"
#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CTextureLoader.h"
#include "CInput.h"

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


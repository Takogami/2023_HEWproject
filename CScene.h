#pragma once
#include "direct3d.h"

class CScene
{
private:

public:
	CScene();	//�R���X�g���N�^
	~CScene();	//�f�X�X�g���N�^
	//�I�[�o�[���C�h�O��̊֐�
	virtual void Update() = 0;	//�V�[���̍X�V����
	virtual void Draw() = 0;	//�`��

};


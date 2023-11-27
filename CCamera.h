//--------------------------------------------------------------------------
// CCamera.h
// 
// �쐬��:�� �K�G
// 
// �T�v:�J�������쐬�ł���N���X
//      Update���\�b�h�ŏ�ɍs����쐬���AGetMatrixView���\�b�h�ōs���n��
//      SetCameraPosition���\�b�h�ňʒu���w�肷�邱�Ƃ��\
// 
// �ŏI�X�V����:2023/10/27
//--------------------------------------------------------------------------

#pragma once

/* �C���N���[�h */
#include "direct3d.h"

//CCamera�N���X
class CCamera
{
private:
	/* �����o�ϐ� */

	DirectX::XMVECTOR eye;		// �ڂ̈ʒu
	DirectX::XMVECTOR focus;	// �ǂ������Ă��邩
	DirectX::XMVECTOR up;		// �J�����̏����

	// View�ϊ��s��
	DirectX::XMMATRIX matrixView;

public:
	/* �����o�ϐ� */

	//�J�����ʒu
	DirectX::XMFLOAT2 cameraPos;

	/* ���\�b�h */

	// �R���X�g���N�^
	CCamera();
	// �f�X�g���N�^
	~CCamera();
	// View�ϊ��s��̎擾
	DirectX::XMMATRIX GetMatrixView();

	// View�ϊ��s��̍X�V
	void Update();
};


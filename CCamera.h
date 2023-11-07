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
//aaa

/* �C���N���[�h */
#include "direct3d.h"

//CCamera�N���X
class CCamera
{
private:
	/* �����o�ϐ� */

	//�J�����ʒu
	DirectX::XMFLOAT2 cameraPos;

	DirectX::XMVECTOR eye;		// �ڂ̈ʒu
	DirectX::XMVECTOR focus;	// �ǂ������Ă��邩
	DirectX::XMVECTOR up;		// �J�����̏����

	// View�ϊ��s��
	DirectX::XMMATRIX matrixView;

public:
	/* ���\�b�h */

	// �R���X�g���N�^
	CCamera();
	// �f�X�g���N�^
	~CCamera();
	// �J�����ʒu�̐ݒ�
	void SetCameraPosition(float pos_x = 0.0f, float pos_y = 0.0f);
	// View�ϊ��s��̎擾
	DirectX::XMMATRIX GetMatrixView();

	// View�ϊ��s��̍X�V
	void Update();
};


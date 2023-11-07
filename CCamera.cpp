//--------------------------------------------------------------------------
// CCamera.cpp
// 
// �쐬��:�� �K�G
// 
// �T�v:�J�������쐬�ł���N���X
//      ���̃t�@�C���ł̓��\�b�h�̖{�̂��L�q���Ă���
//      Update���\�b�h�ŏ�ɍs����쐬���AGetMatrixView���\�b�h�ōs���n��
//      SetCameraPosition���\�b�h�ňʒu���w�肷�邱�Ƃ��\
// 
// �ŏI�X�V����:2023/10/27
//--------------------------------------------------------------------------


//	�����ɒǉ�

/* �C���N���[�h */
#include "CCamera.h"

// �R���X�g���N�^
CCamera::CCamera()
{
	// �P�ʍs��̏�����
	matrixView = DirectX::XMMatrixIdentity();

	// XMVECTOR�^�ϐ��̏�����
	eye = DirectX::XMVectorZero();
	focus = DirectX::XMVectorZero();
	up = DirectX::XMVectorZero();

	//�J�����ʒu�̏�����
	cameraPos = { 0, 0 };
}

// �f�X�g���N�^
CCamera::~CCamera()
{
}

// �J�����ʒu��ݒ�
void CCamera::SetCameraPosition(float pos_x, float pos_y)
{
	//�J�����|�W�V�����̃Z�b�g
	cameraPos = { pos_x, pos_y };
}

// View�ϊ��s��̍X�V
void CCamera::Update()
{
	//View�ϊ��s��̍쐬 �� �J�����p�̍s��
	eye = DirectX::XMVectorSet(cameraPos.x, cameraPos.y, -1, 0);	//���_�̈ʒu
	focus = DirectX::XMVectorSet(cameraPos.x, cameraPos.y, 1, 0);	//���Ă���ʒu
	up = DirectX::XMVectorSet(0, 1, 0, 0);							//�J�����̏����

	matrixView = DirectX::XMMatrixLookAtLH(eye, focus, up);
}

// View�ϊ��s��̎擾
DirectX::XMMATRIX CCamera::GetMatrixView()
{
	return matrixView;
}


#pragma once			//�d���C���N���[�h�������h�~����

#include <d3d11.h>		//DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h>//DirectX�̐��w�֘A�̃w�b�_�[�t�@�C��
#include "DirectWhite.h"

//DirectX�̉���̊ȗ����}�N��
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

//�\���̂̒�`
//xy��\���\����
struct FLOAT_XY
{
	float x, y;
};

//�萔�o�b�t�@�p�\����
struct ConstBuffer
{
	//UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;
	//���e�s��
	DirectX::XMMATRIX matrixProj;
	//���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;
	//���f���ɓK�p����}�e���A���F
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };
};

//�v���g�^�C�v�錾
HRESULT D3D_Create(HWND hwnd);
void    D3D_Release();

//�l�p�`�|���S�����쐬���A���_�o�b�t�@�������s��
//����4����:�|�C���^�^�ϐ��̃A�h���X������̂�*����t��
void D3D_CreateSquare(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vd);

//�e�N�X�`����ǂݍ���
//����:(1)�t�@�C���� (2)�e�N�X�`���i�[�p�ϐ��̃A�h���X
HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture);

//��ʓh��Ԃ��Ɛݒ���s���֐�
void D3D_ClearScreen();

//��ʍX�V����֐�
void D3D_UpdateScreen();

//�O���[�o���ϐ���extern�錾
//�������܂Ŗ�����O���Ɍ��J���Ă��邾���Ȃ̂ŐV�����ϐ�������Ă���킯�ł͂Ȃ�

extern ID3D11DeviceContext* m_pImmediateContext;   //�R���e�L�X�g = �`��֘A���i��@�\
extern const UINT strides;
extern const UINT offsets;

extern ID3D11BlendState* m_pBlendStateAlpha;       //�u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�j
extern ID3D11BlendState* m_pBlendStateAdditive;    //�u�����h�X�e�[�g�p�ϐ��i���Z�����j

// �萔�o�b�t�@�p�ϐ���cpp�Ɍ��J
extern ID3D11Buffer* m_pConstBuffer;
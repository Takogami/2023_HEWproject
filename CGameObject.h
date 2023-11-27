//--------------------------------------------------------------------------
// CGameObject.h
// 
// �쐬��:�� �K�G
// 
// �T�v:��{�Q�[���I�u�W�F�N�g�N���X�𐶐�����N���X
//      ���N���X�Ƃ��Ďg�p���邱�Ƃ𐄏�
//      �Z�b�g��CTransform�N���X���g�p���邱��
// 
//      10/24:�J�����ɑΉ�
//            SetUsingCamera()�Ŏg�p����J�����̐ݒ�
// 
// �ŏI�X�V����:2023/10/24
//--------------------------------------------------------------------------

#pragma once

/* �C���N���[�h */
#include "direct3d.h"
#include "CTransform.h"

/* CCamera�N���X�̑O���錾 */
class CCamera;

// BoxCollider�^�̒�`
struct BoxCollider
{
	float centerX;	// Box�R���C�_�[�̒��S�_X
	float centerY;	// Box�R���C�_�[�̒��S�_Y
	float sizeX;	// Box�R���C�_�[��x�����̑傫��
	float sizeY;	// Box�R���C�_�[��y�����̑傫��
};

//CGameObject�N���X
class CGameObject
{
protected:
	/* �����o�ϐ� */

	ID3D11Buffer* vertexBuffer;			//�`��Ɏg�p���钸�_�o�b�t�@
	ID3D11ShaderResourceView* texture;	//�e�N�X�`���ϐ�
	FLOAT_XY uv = { 0.0f,0.0f };		//uv�����p(�A�j���[�V�����Ɏg�p)

	CCamera* useCamera;					//�`��Ɏg�p����J�����̃|�C���^

public:
	/* �����o�ϐ� */

	CTransform transform;								//���z���E�̒��̈ʒu���W,�X�P�[��,��]��
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	//�}�e���A���F�̐ݒ�
	BoxCollider Bcol = { 0.0f, 0.0f, 0.0f, 0.0f };		// Box�R���C�_�[�p�����[�^

	/* ���\�b�h */

	//����������(�R���X�g���N�^) ����1:���_�o�b�t�@ ����2:�e�N�X�`�� ����3:�e�N�X�`���ړ���
	//�� ����3 ��uv�������Ȃ��Ȃ���͂̕K�v�͂���܂���
	CGameObject(ID3D11Buffer*, ID3D11ShaderResourceView*, FLOAT_XY _uv = { 1.0f,1.0f });
	//�I������(�f�X�g���N�^)
	virtual ~CGameObject();

	//�Q�[�����[�v���ƂɎ��s���鏈��
	virtual void Update();
	//�Q�[�����[�v���Ƃɕ`�悷�鏈��
	virtual void Draw();

	//�}�e���A���F�Z�b�g�p�֐�
	void SetMaterial(DirectX::XMFLOAT4 material) { materialDiffuse = material; };
	//�g�p����J������ݒ�
	void SetUseingCamera(CCamera* setCamera);
};


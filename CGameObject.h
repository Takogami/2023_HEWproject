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
#include "CCollision.h"
#include "CAnimation.h"

/* CCamera�N���X�̑O���錾 */
class CCamera;

// �I�u�W�F�N�g�̎��
enum class OBJECT_TYPE
{
	NORMAL,		// �ʏ�I�u�W�F�N�g
	PLAYER,		// �v���C���[�I�u�W�F�N�g
	WIND_RIGHT,	// ���I�u�W�F�N�g�i�E�����j
	WIND_LEFT,	//���I�u�W�F�N�g�i�������j
	WIND_UP,	// ���I�u�W�F�N�g�i������j
	DAMAGE_TILE,//�_���[�W���󂯂鏰
	ENEMY,		// �G�I�u�W�F�N�g
};

//CGameObject�N���X
class CGameObject
{
protected:
	/* �����o�ϐ� */

	ID3D11Buffer* vertexBuffer;			//�`��Ɏg�p���钸�_�o�b�t�@
	ID3D11ShaderResourceView* texture;	//�e�N�X�`���ϐ�

	FLOAT_XY uv = { 0.0f,0.0f };		//uv�����ړ���(�A�j���[�V�����Ɏg�p)
	FLOAT_XY sprit = { 0.0f,0.0f };		//1�R�}�̃T�C�Y

	CCamera* useCamera;					//�`��Ɏg�p����J�����̃|�C���^
	CAnimation* anim;					//�A�j���[�V�����N���X
	bool anim_switch = false;			//�A�j���[�V�����̍s�����̃t���O

	OBJECT_TYPE objectType = OBJECT_TYPE::NORMAL; // 1: �ǂ⏰, 2: �G �Ȃ�

public:
	/* �����o�ϐ� */
	CTransform transform;								// ���z���E�̒��̈ʒu���W,�X�P�[��,��]��
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// �}�e���A���F�̐ݒ�
	BoxCollider Bcol = { 0.0f, 0.0f, 0.0f, 0.0f };		// Box�R���C�_�[�p�����[�^

	/* ���\�b�h */

	//����������(�R���X�g���N�^) ����1:���_�o�b�t�@ ����2:�e�N�X�`�� ����3:�e�N�X�`���ړ���, ����4:�I�u�W�F�N�g��ID 
	//�� ����3 ��uv�������Ȃ��Ȃ���͂̕K�v�͂���܂��� ����4 �ʏ�I�u�W�F�N�g�̏ꍇ�͓��͂̕K�v�͂���܂���
	CGameObject(ID3D11Buffer*, ID3D11ShaderResourceView*, FLOAT_XY uv = { 1.0f,1.0f }, OBJECT_TYPE type = OBJECT_TYPE::NORMAL);
	//�I������(�f�X�g���N�^)
	virtual ~CGameObject();

	//�Q�[�����[�v���ƂɎ��s���鏈��
	virtual void Update();
	//�Q�[�����[�v���Ƃɕ`�悷�鏈��
	virtual void Draw();
	//�g�p����J������ݒ�
	void SetUseingCamera(CCamera* setCamera);

	//�A�j���[�V�����̏�����
	//����1:�����̍Đ���� ����2:�������̕����� ����3:�����A�j���[�V�����p�^�[�� ����4:�����X�s�[�h
	void InitAnimParameter(bool iniPlaying, int spritU, int spritV, ANIM_PATTERN pattern, float sp);
	// �A�j���[�V�����̃X�s�[�h��ݒ�
	void SetAnimationSpeed(float sp);
	// �A�j���[�V�����̃p�^�[����ݒ�
	void SetAnimationPattern(ANIM_PATTERN pattern);
	// �A�j���[�V�����̍Đ�
	void PlayAnimation();
	// �A�j���[�V�����̒�~
	void StopAnimation();
	// �A�j���[�V�����̃��Z�b�g
	void ResetAnimation();

	//�e�N�X�`���̐؂蔲��
	//����1:u�����̉��Ԗڂ�؂蔲����  ����2:v�����̉��Ԗڂ�؂蔲����
	void TextureCutout(int u_num, int v_num);

	// �Q�[���I�u�W�F�N�g�̎�ނ��Z�b�g
	void SetObjectType(OBJECT_TYPE _objectType);
	// �Q�[���I�u�W�F�N�g�̎�ނ��擾
	OBJECT_TYPE GetObjectType() const;
};


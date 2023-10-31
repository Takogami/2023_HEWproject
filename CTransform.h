//--------------------------------------------------------------------------
// CTranceform.h
// 
// �쐬��:�� �K�G
// �T�v:�Q�[���I�u�W�F�N�g�̈ʒu�A�傫��(�X�P�[��)�A��]����ێ�����N���X
// 
// �ŏI�X�V����:2023/10/12
//--------------------------------------------------------------------------

#pragma once

//FLOAT3�\����
//float�^�̒l���R�i�[
typedef struct
{
	float x;	//x�l
	float y;	//y�l
	float z;	//z�l
}VECTOR3;

//CTranceform�N���X
class CTransform
{

public:

	/* �����o�ϐ� */

	VECTOR3 position;	//�ʒu���W
	VECTOR3 scale;		//�X�P�[��
	float rotation;		//��]��

	/* ���\�b�h */
	
	CTransform();			//�R���X�g���N�^ �e���l�̏��������s��
	~CTransform();			//�f�X�g���N�^

	// *���Z�q�̃I�[�o�[���[�h
	// �䗦���ێ����Ċg��A�k���������@��2D�̂ݑΉ�
	inline void operator *(float n)
	{
		this->scale.x *= n;
		this->scale.y *= n;
	}
};
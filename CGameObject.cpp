//--------------------------------------------------------------------------
// CGameObject.cpp
// 
// �쐬��:�� �K�G
// 
// �T�v:��{�Q�[���I�u�W�F�N�g�N���X�𐶐�����N���X
//      ���̃t�@�C���ł̓��\�b�h�̖{�̂��L�q���Ă���
//      ���N���X�Ƃ��Ďg�p���邱�Ƃ𐄏�
//      �Z�b�g��CTransform�N���X���C���N���[�h���邱��
// 
//       10/24:�J�����ɑΉ�
//             SetUsingCamera()�Ŏg�p����J�����̐ݒ�
// 
// �ŏI�X�V����:2023/10/24
//--------------------------------------------------------------------------

/* �C���N���[�h */
#include "CGameObject.h"
#include "CCamera.h"

/* ���O��� */
using namespace DirectX;

//�R���X�g���N�^
CGameObject::CGameObject(ID3D11Buffer* _vb, ID3D11ShaderResourceView* _tex, FLOAT_XY _uv)
{
	//�g�p�J�����̏�����
	useCamera = nullptr;

	//���f���̍쐬
	D3D_CreateSquare({ 0.0f ,0.0f }, { 1.0f ,1.0f }, _uv, &_vb);

	//uv�����̐ݒ�
	sprit = _uv;

	//�����Ŏ󂯎�������_�o�b�t�@�ƃe�N�X�`�����Z�b�g����
	vertexBuffer = _vb;
	texture = _tex;
}

//�f�X�g���N�^
CGameObject::~CGameObject()
{
	SAFE_RELEASE(vertexBuffer);
}

//Update
void CGameObject::Update()
{
	//�S�ẴI�u�W�F�N�g���ʂ�Update����

	//�I�u�W�F�N�g�̈ʒu�ƃR���C�_�[�̒��S�����킹��
	this->Bcol.centerX = this->transform.position.x;
	this->Bcol.centerY = this->transform.position.y;

	//������Update�������L�q����
	//���ʏ����ȊO�͌p�����override���ċL�q���邱��
}

//Draw
void CGameObject::Draw()
{
	//�R���X�g�o�b�t�@�̍쐬
	ConstBuffer cb;

	//���s���e�̍s��쐬
	//��P,��Q�����F�f���o�����c�̒���
	//��R,��S�����F�f���o����Ԃ̉��s(��O�ƍŉ�)
	float scaleScreen = 1.0f;		//���[���h�̃X�P�[��
	cb.matrixProj = XMMatrixOrthographicLH(4.0f * scaleScreen, 2.25f * scaleScreen, 0.0f, 3.0f);

	//�J�������ݒ肳��Ă���Ȃ�J�����̍s����������킹��
	cb.matrixProj = useCamera != nullptr ?
		XMMatrixTranspose(useCamera->GetMatrixView() * cb.matrixProj) : XMMatrixTranspose(cb.matrixProj);

	//�ړ��s��
	XMMATRIX matrixMove = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
	//�g��k���s��
	XMMATRIX matrixScale = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	//��]�s��
	XMMATRIX matrixRotation = XMMatrixRotationZ(XMConvertToRadians(transform.rotation));
	//�s��͊|���Z�ō����ł��� ���|���鏇�Ԃ��e������ ����͊g��A�k�����Ă���ړ��ړ�������
	cb.matrixWorld = matrixScale * matrixRotation * matrixMove;
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	//UV�A�j���[�V�����̍s����쐬
	// XMMatrixTranslation���ړ��s������֐�
	cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	// XMMatrixTranspose���]�u�s������
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	//�}�e���A���F���V�F�[�_�[�ɃZ�b�g
	cb.materialDiffuse = materialDiffuse;

	//�s����V�F�[�_�[�ɓn��
	m_pImmediateContext->UpdateSubresource(m_pConstBuffer, 0, NULL, &cb, 0, 0);

	//������Draw���钸�_�o�b�t�@(���f��)���w�肷��
	m_pImmediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offsets);
	//�s�N�Z���V�F�[�_�[�Ƀe�N�X�`����n��
	m_pImmediateContext->PSSetShaderResources(0, 1, &texture);
	//�`�施��
	//�������͕`�悷�钸�_�̐�
	m_pImmediateContext->Draw(6, 0);
}

//�g�p����J������ݒ������
void CGameObject::SetUseingCamera(CCamera* setCamera)
{
	//�J�����̃|�C���^���󂯎��
	useCamera = setCamera;
}

void CGameObject::TextureCutout(int u_num, int v_num)
{
	//�w�肳�ꂽ�������e�N�X�`�����ړ�������
	uv.x = sprit.x * u_num;
	uv.y = sprit.y * v_num;
}

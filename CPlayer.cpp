#include "CPlayer.h"
#include "CInput.h"
#include "CScene.h"

//�����I�ɐe�N���X�̃R���X�g���N�^���Ăяo��
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv) : CGameObject(vb, tex, uv)
{
}

void CPlayer::Update()
{
	// ������߂�
	dir.x = 0.0f;
	dir.y = 0.0f;

	// �ړ�����
	if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyPress(VK_DOWN)))
	{
		dir.y = -1.0f;
	}
	else if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyPress(VK_UP))
	{
		dir.y = 1.0f;
	}
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT) || gInput->GetKeyPress(VK_LEFT))
	{
		dir.x = -1.0f;
	}
	else if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || gInput->GetKeyPress(VK_RIGHT))
	{
		dir.x = 1.0f;
	}

	//�P�ʃx�N�g����(�����P�ɂ���) = ���K��
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// �x�N�g���v�Z�p�̌^�ɓ����
	v = DirectX::XMVector3Normalize(v);					// ���K������
	DirectX::XMStoreFloat3(&dir, v);					// ���̕ϐ�dir�ɖ߂�

	// �x�N�g���ɑ��x�������Ĉʒu��ύX
	this->transform.position.x += dir.x * 0.03f;
	this->transform.position.y += dir.y * 0.03f;

	// �e�N���X��Update()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̍X�V�������s��
	CGameObject::Update();
}

void CPlayer::Draw()
{
	// �e�N���X��Draw()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̕`�揈�����s��
	CGameObject::Draw();
}


CPlayer::~CPlayer()
{
	// �e�N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo��
	// ���_�o�b�t�@�̉�����s��
	CGameObject::~CGameObject();
}

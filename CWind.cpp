#include "CWind.h"

//�����I�ɐe�N���X�̃R���X�g���N�^���Ăяo��
CWind::CWind(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
}

CWind::~CWind()
{
	// �e�N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo��
	// ���_�o�b�t�@�̉�����s��
	CGameObject::~CGameObject();
}

void CWind::Update()
{
	// �e�N���X�̍X�V�𖾎��I�ɌĂяo��
	CGameObject::Update();
}

void CWind::SetWindStrangth(float power)
{
	// �ύX�O�̍��W��ۑ�
	windStrength = power;
}

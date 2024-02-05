#include "CCursor.h"
#include "CInput.h"

CCursor::CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex) : CGameObject(vb, tex, uv)
{
}

void CCursor::Update()
{
	// �ړ�����
	if ((gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyTrigger(VK_DOWN)))
	{
		scene_count++;// ����1�i�߂�
	}
	else if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyTrigger(VK_UP))
	{
		scene_count += SCENE_COUNT-1;// ���1�i�߂�
	}

	// �^�C�g���̑I�����ڐ��𒴉߂����ꍇ�ɐ������킹��
	// (scene_count��0�`SCENE_COUNT-1�̊ԂɂȂ�悤�ɒ���)
	scene_count %= SCENE_COUNT;

	// �J�[�\���̈ʒu����
	this->transform.position.y = ini_position.y - moveDistance * scene_count;

	gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A);

	CGameObject::Update();
}

void CCursor::Draw()
{
	// �e�N���X��Draw()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̕`�揈�����s��
	CGameObject::Draw();
}

void CCursor::Init(FLOAT_XY ini_pos, float move)
{
	ini_position = ini_pos;
	moveDistance = move;
}

//CCursor�ł̗񋓌^��Scene���擾����
CCursor_Point CCursor::GetCursorPoint() const
{
	switch (scene_count)
	{
	case 0:
		return CCursor_Point::STAGE;
	case 1:
		return CCursor_Point::OPTION;
	case 2:
		return CCursor_Point::EXIT;
	default:
		// �G���[������f�t�H���g�̋�����ݒ�
		return CCursor_Point::STAGE; // ���̒l�ł��B�K�؂ȏ����ɕύX���Ă��������B
	}
}

CCursor::~CCursor()
{

	// �e�N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo��
	// ���_�o�b�t�@�̉�����s��
	CGameObject::~CGameObject();
}


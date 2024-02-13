#include "CCursor.h"
#include "CInput.h"
#include "CEase.h"

CCursor::CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// �C�[�W���O�̎��̉�
	curEase = new CEase;
}

void CCursor::CursorInput()
{
	// �I�u�W�F�N�g���A�N�e�B�u�łȂ��Ȃ�X�V�͍s��Ȃ�
	if (!active)
	{
		return;
	}

	// �ړ�����
	if ((gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyTrigger(VK_DOWN)))
	{
		scene_count++;// ����1�i�߂�
	}
	else if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyTrigger(VK_UP))
	{
		scene_count += sceneNum - 1;// ���1�i�߂�
	}

	// �^�C�g���̑I�����ڐ��𒴉߂����ꍇ�ɐ������킹��
	// (scene_count��0�`SCENE_COUNT-1�̊ԂɂȂ�悤�ɒ���)
	scene_count %= sceneNum;

	// �J�[�\���̈ʒu����
	this->transform.position.y = ini_position.y - moveDistance * scene_count;
}

void CCursor::Update()
{
	// �I�u�W�F�N�g���A�N�e�B�u�łȂ��Ȃ�X�V�͍s��Ȃ�
	if (!active)
	{
		return;
	}

	// �C�[�W���O�̏���
	curEase->Update();
	if (curEase->GetState() == STATE::END)
	{
		// �܂�Ԃ��ł��鎞
		if (!curReturn)
		{
			curEase->Init(&transform.position.x, transform.position.x - 0.02f, 0.5f, 0, EASE::easeOutExpo);
			// �܂�Ԃ��t���O���グ��
			curReturn = true;
		}
		else
		{
			curEase->Init(&transform.position.x, transform.position.x + 0.02f, 0.5f, 0, EASE::easeInExpo);
			// �܂�Ԃ��t���O��������
			curReturn = false;
		}
	}

	CGameObject::Update();
}

void CCursor::Draw()
{
	// �I�u�W�F�N�g���A�N�e�B�u�łȂ��Ȃ�X�V�͍s��Ȃ�
	if (!active)
	{
		return;
	}

	// �e�N���X��Draw()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̕`�揈�����s��
	CGameObject::Draw();
}

void CCursor::Init(FLOAT_XY ini_pos, int scene, float move)
{
	// �J�ڂł���V�[������ݒ�
	sceneNum = scene;
	// �����ʒu�ƈړ��ʂ�ݒ�
	ini_position = ini_pos;
	moveDistance = move;
	// �����ʒu�������Ă���
	transform.position.x = ini_position.x;
	transform.position.y = ini_position.y;
	// �C�[�W���O�̏�����
	curEase->Init(&transform.position.x, transform.position.x + 0.02f, 0.5f, 0, EASE::easeInExpo);
}

//CCursor�ł̗񋓌^��Scene���擾����
CCursor_Point CCursor::GetCursorPoint() const
{
	if (!active)
	{
		return CCursor_Point::INACTIVE;
	}

	switch (scene_count)
	{
	case 0:
		return CCursor_Point::STAGE;
	case 1:
		return CCursor_Point::EXIT;
	case 2:
		return CCursor_Point::INACTIVE;
	default:
		// �G���[������f�t�H���g�̋�����ݒ�
		return CCursor_Point::INACTIVE; // ���̒l�ł��B�K�؂ȏ����ɕύX���Ă��������B
	}
}

CCursor::~CCursor()
{
	delete curEase;

	// �e�N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo��
	// ���_�o�b�t�@�̉�����s��
	CGameObject::~CGameObject();
}


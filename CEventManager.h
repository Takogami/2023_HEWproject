#pragma once

// �v���C���[�̗̑�
#define PLAYER_HP (6)

/* �O���錾 */
class CTimer;

// �Q�[���̐i�s���
enum class GAME_STATE
{
	READY,	// �X�^�[�g�O
	START,	// �Q�[���J�n(��)
	TIME_UP,// �^�C���A�b�v
	ZERO_HP,// �v���C���[��HP��0
};

class CEventManager
{
private:
	// �Q�[���̎��ԊǗ�
	CTimer* gameTime;
	// �v���C���[��HP
	int playerHP = PLAYER_HP;
	// �X�R�A
	int score = 0;
	// �Q�[���̐i�s���
	GAME_STATE state = GAME_STATE::READY;

	// �B��̃C���X�^���X
	static CEventManager* instance;

	// �R���X�g���N�^
	CEventManager();
	// �f�X�g���N�^
	~CEventManager();
	//�A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();

public:
	// �C���X�^���X�̎擾
	static CEventManager* GetInstance();

	// ������
	void Init();
	// �X�V
	void Update();

	// �X�R�A�̉��Z
	// ����1 : ���Z����X�R�A
	void AddScore(int addScore);

	// �Q�[���̐i�s��Ԃ��擾
	GAME_STATE GetGameState();
};


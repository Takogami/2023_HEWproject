#pragma once
#include "direct3d.h"
#include <list>

// �v���C���[�̗̑�
#define PLAYER_HP (6)

/* �O���錾 */
class CTimer;
class CGameObject;
class CEase;

// �Q�[���̐i�s���
enum class GAME_STATE
{
	READY,	// �X�^�[�g�O
	START,	// �Q�[���J�n(��)
	TIME_UP,// �^�C���A�b�v
	ZERO_HP,// �v���C���[��HP��0
};

class CGameManager
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

	// UI�p�̒��_�o�b�t�@
	ID3D11Buffer* vertexBufferUI;

	// �X�R�A�{�[�h
	CGameObject* UI_hpBoard;
	// �^�C�}�[�̔w�i
	CGameObject* UI_timer;
	// HP��UI
	CGameObject* UI_hp[3];
	// �_���[�W���󂯂��Ƃ��̃n�[�g
	CGameObject* UI_breakHeart_R[3];
	CGameObject* UI_breakHeart_L[3];
	// �n�[�g�������鉉�o�̃C�[�W���O
	CEase* breakHeart_R_ease[3];
	CEase* breakHeart_L_ease[3];
	// �n�[�g�̓����x��ύX�������̃t���O
	bool heartAlpha_R[3] = { false };
	bool heartAlpha_L[3] = { false };

	// �I�u�W�F�N�g�̃��X�g
	std::list<CGameObject*> Objects;

	// �B��̃C���X�^���X
	static CGameManager* instance;

	// �R���X�g���N�^
	CGameManager();
	// �f�X�g���N�^
	~CGameManager();

	// �̗�UI�̍X�V
	void UpdateUIhp();

	//�A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();

public:
	// �C���X�^���X�̎擾
	static CGameManager* GetInstance();

	// ������
	void Init();
	// �X�V
	void Update();
	// �Q�[���V�X�e���֘A��UI�̕`��
	void Draw();

	// �X�R�A�̉��Z
	// ����1 : ���Z����X�R�A
	void AddScore(int addScore);
	// �X�R�A�̉��Z
	// ����1 : �_���[�W�l(1~6)
	void AddDamage(int addDamage);

	// �Q�[���̐i�s��Ԃ��擾
	GAME_STATE GetGameState();
};


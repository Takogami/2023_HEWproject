#pragma once
#include "CGameObject.h"
#include "CTextureLoader.h"
#include "CCamera.h"

//�����̌^����ʖ��ł��g����悤�ɂ���
typedef ID3D11ShaderResourceView* D3DTEXTURE;

//�����ɒǉ�

//�Q�[���S�̂�\���N���X
class CGame
{
public:
	//�񋓌^
	//��ʂ̏��
	enum SCENE_STATE {
		NO_SCENE,
		TITLE,
		STAGE,
		RESULT,
	};

	//�t�F�[�h���
	enum FADE_STATE {
		NO_FADE,
		FADE_IN,
		FADE_OUT,
	};

	FADE_STATE fadeState = NO_FADE;

	DirectX::XMFLOAT2 cameraPos = { 0, 0 };	//�J�����ʒu
	CCamera* Cam;

private:

	SCENE_STATE scene = TITLE;		//���݂̉��
	SCENE_STATE newScene = NO_SCENE;

	//�����o�ϐ�
	ID3D11Buffer* vertexBufferCharacter;		//�Q�[���Ŏg�����f��(���_�o�b�t�@)
	
	CGameObject* player;			//�v���C���[
	CGameObject* player2;			//�v���C���[
	CTextureLoader* TexLoader;		//�V���O���g���󂯎��p

	//�e��ʂ̍X�V�����֐�
	void UpdateTitle();		//�^�C�g�����

public:
	//�����o�֐�
	CGame();								//����������(�R���X�g���N�^)
	void Update();							//�Q�[�����[�v���Ɏ��s���鏈���������֐�
	void SetScene(SCENE_STATE nextScene);	//�V�[���ύX�֐�
	~CGame();								//�I������(�f�X�g���N�^)
};
//�������폜

extern CGame* gGame;

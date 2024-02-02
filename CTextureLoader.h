//-------------------------------------------------------------------------------
// CTextureLoader.h
// 
// �쐬��:�� �K�G
// 
// �T�v:�e�N�X�`�������[�h���A�����Ԃ��N���X
//      �V���O���g���Ŏ������Ă��邽�߁A�B��̃C���X�^���X���擾����K�v������
//      �p�X�Ǝ��ʎq��ǉ����邾���Ńe�N�X�`���̃��[�h���s����
// 
//      10/30:enum�N���X���O�Ɉړ�
//            GetTex��ID�w�肪�ȒP��
// 
// �ŏI�X�V����:2023/10/30
//-------------------------------------------------------------------------------

#pragma once

/* �C���N���[�h */
#include "direct3d.h"
#include <list>

// �e�N�X�`�����i�[�p�\����
// �p�X�ƃe�N�X�`����ǂݍ��ޕϐ��̃|�C���^
typedef struct
{
	const wchar_t* path;
	ID3D11ShaderResourceView* tex;
}TEX_INFO;

enum class TEX_ID	// �e�N�X�`�����ʎq�񋓌^
{
	CHAR1,
	TAKO,
	STAGE,
	NUM,
	WINDRIGHT_POS,	//	���̋N����ʒu�i�E�����j
	TITLE,
	TILE,
	BG,
	PLAYER,
	BOOK,
	STRING_BG,
	GAMEOVER
};

// CTextureLoader�N���X
class CTextureLoader
{
private:
	/* �����o�ϐ� */
 
	static CTextureLoader* instance;		// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^

	std::list<TEX_INFO> texList;			// �e�N�X�`�����̃��X�g
	std::list<const wchar_t*> pathList =	// �p�X�̃��X�g
	{
		L"asset/char01.png",
		L"asset/Tako.jpg",
		L"asset/Madoka_Magika_(Logo).png",
		L"asset/suuji.png",
		L"asset/Fade.png",	//	�����Ńe�N�X�`���ǂݍ���(���̉E����)
		L"asset/title.png",
		L"asset/tile.png",
		L"asset/bg.png",
		L"asset/Playeranim3.png",
		L"asset/book.png",
		L"asset/stringBg.png",
		L"asset/GameOver.png",
	};

	/* ���\�b�h */

	CTextureLoader();				//�R���X�g���N�^
	~CTextureLoader();				//�f�X�g���N�^

	static void CleanupSingleton();	//�A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)

public:
	/* ���\�b�h */

	void LoadTexture();							// �e�N�X�`�������[�h����
	void UnloadTexture();						// �e�N�X�`�����A�����[�h����

	ID3D11ShaderResourceView* GetTex(TEX_ID id);// �e�N�X�`�����擾����

	static CTextureLoader* GetInstance();		//�C���X�^���X���擾���邽�߂̃��\�b�h
};


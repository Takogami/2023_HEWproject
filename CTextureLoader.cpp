//-------------------------------------------------------------------------------
// CTextureLoader.cpp
// 
// �쐬��:�� �K�G
// 
// �T�v:�e�N�X�`�������[�h���A�����Ԃ��N���X
//      ���̃t�@�C���ł̓��\�b�h�̖{�̂��L�q���Ă���
//      �V���O���g���Ŏ������Ă��邽�߁A�B��̃C���X�^���X���擾����K�v������
//      �p�X�Ǝ��ʎq��ǉ����邾���Ńe�N�X�`���̃��[�h���s����
// 
//      10/30:enum�N���X���O�Ɉړ�
//            GetTex��ID�w�肪�ȒP��
// 
// �ŏI�X�V����:2023/10/30
//-------------------------------------------------------------------------------

/* �C���N���[�h */
#include "CTextureLoader.h"

// CTextureLoader�N���X��static�����o�ϐ��̏�����
CTextureLoader* CTextureLoader::instance = nullptr;

//�R���X�g���N�^
CTextureLoader::CTextureLoader()
{
	//�p�X�̃��X�g�̓��e��S��texList��push����
	for (std::list<const wchar_t*>::iterator it = pathList.begin(); it != pathList.end(); ++it)
	{
		//path�����X�g�ɒǉ�
		texList.push_back({ *it, nullptr});
	}
}

//�f�X�g���N�^
CTextureLoader::~CTextureLoader()
{
}

//�S�Ẵe�N�X�`�������[�h����
void CTextureLoader::LoadTexture()
{
	//texList�Ɋi�[���ꂽ�p�X�̐������e�N�X�`����ǂݍ���
	for (std::list<TEX_INFO>::iterator it = texList.begin(); it != texList.end(); ++it)
	{
		//�e�N�X�`���ǂݍ���
		D3D_LoadTexture(it->path, &it->tex);
	}
}

//�S�Ẵe�N�X�`�����A�����[�h����
void CTextureLoader::UnloadTexture()
{
	//texList���̃|�C���^�ϐ����������
	for (std::list<TEX_INFO>::iterator it = texList.begin(); it != texList.end(); ++it)
	{
		//�����������
		SAFE_RELEASE(it->tex);
	}
}

//�e�N�X�`���̎擾���s���֐�
//������ �N���X��::TEX_ID::�C�ӂ�ID �Ŏw�肷�邱��
ID3D11ShaderResourceView* CTextureLoader::GetTex(TEX_ID id)
{
	//�C�e���[�^�̏�����
	std::list<TEX_INFO>::iterator it = texList.begin();
	//�n���ꂽid�̃e�N�X�`�����Q�Ƃ���
	std::advance(it, (int)id);

	//�C�e���[�^���̗v�f���Q�Ƃ��A���̓���tex��Ԃ�
	return it->tex;
}

//�B��̃C���X�^���X��Ԃ��֐�
CTextureLoader* CTextureLoader::GetInstance()
{
	// �V���O���g�������݂��Ă��Ȃ��Ȃ琶������
	if (!instance)
	{
		// �V���O���g���̐���
		instance = new CTextureLoader();
		//�R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}
	//�B��̃C���X�^���X��Ԃ�
	return instance;
}

//�V���O���g���̉������
void CTextureLoader::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

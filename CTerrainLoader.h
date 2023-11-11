#pragma once

/* �C���N���[�h */
#include <vector>
#include <string>

// �n�`�f�[�^�̎��ʎq
enum class TERRAIN_ID
{
	STAGE_1,
};

// CStageCreate�N���X
class CTerrainLoader
{
private:
	/* �����o�ϐ� */

	// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^
	static CTerrainLoader* instance;
	// �P�u���b�N�̃T�C�Y
	const float tile_size = 0.15f;
	// �X�e�[�W�f�[�^�̃t�@�C����
	std::vector<std::string> file_name = 
	{
		"stage1_data.csv",
	};
	// ������A���Ŋ����������p�X�̏����i�[
	std::vector<std::string> path;
	// �}�b�v�f�[�^�ۑ��p
	std::vector<std::vector<int>> map_info;

	/* ���\�b�h */

	// �R���X�g���N�^
	CTerrainLoader();
	// �f�X�g���N�^
	~CTerrainLoader();
	// �A�v���P�[�V�����I�����ɃR�[���o�b�N�Ƃ��ČĂяo��(�V���O���g���̉��)
	static void CleanupSingleton();

public:
	/* ���\�b�h */

	// �C���X�^���X���擾���邽�߂̃��\�b�h
	static CTerrainLoader* GetInstance();
	// �n�`�f�[�^�̓ǂݍ���
	void LoadTerrainData(TERRAIN_ID stage);
	// �n�`�f�[�^�̎擾���s��
	std::vector<std::vector<int>> GetTerrainData();
};


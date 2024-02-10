#pragma once

/* �C���N���[�h */
#include <vector>
#include <string>

/* �}�N����` */

// �}�b�v���\������I�u�W�F�N�g(�^�C��)�̃T�C�Y
#define TILE_WIDTH		(0.15f)
#define TILE_HEIGHT		(0.15f)

// ��ʍ���̍��W
#define ORIGIN_TILE_POS_X	(-1.924f)
#define ORIGIN_TILE_POS_Y	(1.051f)

// �n�`�f�[�^�̎��ʎq
enum class TERRAIN_ID
{
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
};

// CStageCreate�N���X
class CTerrainLoader
{
private:
	/* �����o�ϐ� */

	// �B��̃C���X�^���X���i�[���邽�߂̃|�C���^
	static CTerrainLoader* instance;
	// �X�e�[�W�f�[�^�̃t�@�C����
	std::vector<std::string> file_name = 
	{
		"stage1_data.csv",
		"stage2_data.csv",
		"stage3_data.csv",
		"stage4_data.csv",
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


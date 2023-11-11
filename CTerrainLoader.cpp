/* �C���N���[�h */
#include "CTerrainLoader.h"
#include "direct3d.h"
#include <fstream>
#include <sstream>

// CTerrainLoader�N���X��static�����o�ϐ��̏�����
CTerrainLoader* CTerrainLoader::instance = nullptr;

// �R���X�g���N�^
CTerrainLoader::CTerrainLoader()
{
	// �t�@�C���̐��������[�v
	for (int i = 0; i < file_name.size(); i++)
	{
		// �p�X�����������Apath�z��Ɋi�[
		path.push_back(file_name[i].insert(0, "./stageTerrain_data/"));
	}
}

// �f�X�g���N�^
CTerrainLoader::~CTerrainLoader()
{
}

// �B��̃C���X�^���X��Ԃ��֐�
CTerrainLoader* CTerrainLoader::GetInstance()
{
	// �V���O���g�������݂��Ă��Ȃ��Ȃ琶������
	if (!instance)
	{
		// �V���O���g���̐���
		instance = new CTerrainLoader();
		//�R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}
	//�B��̃C���X�^���X��Ԃ�
	return instance;
}

// �V���O���g���̉������
void CTerrainLoader::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

// �n�`�f�[�^�̓ǂݍ���
void CTerrainLoader::LoadTerrainData(TERRAIN_ID stage)
{
	// �O�ɓǂݍ��܂ꂽ�����N���A����
	map_info.clear();

	// �ǂݍ��񂾃f�[�^���i�[
	std::string read_buf;

	// �w�肳�ꂽcsv�t�@�C�����J��
	std::ifstream ifs_csv_file(path[(int)stage]);

	// �t�@�C��������ɊJ���Ă��邩�`�F�b�N
	if (!ifs_csv_file.is_open())
	{
		MessageBoxA(NULL, "�w�肳�ꂽ�t�@�C����������܂���", "�G���[", MB_OK | MB_ICONERROR);
		return;
	}

	// �w�b�_�[�s��ǂݔ�΂�
	std::string header;
	getline(ifs_csv_file, header);

	// �f�[�^��ǂݍ���
	for (int i = 0 ;getline(ifs_csv_file, read_buf); i++)
	{
		// �u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
		std::istringstream i_stream(read_buf);
		// �}�b�v���̔z��̗�(�c)�����T�C�Y����
		map_info.resize(map_info.size() + 1);
		// �s�� ','�������܂ŌJ��Ԃ�
		for (int j = 0 ; getline(i_stream, read_buf, ','); j++)
		{
			// �ǂݍ��񂾃f�[�^�𐮐��ɕϊ����čs(��)�̖����ɕۑ�
			map_info[i].push_back(std::stoi(read_buf));
		}
	}

	// �t�@�C�������
	ifs_csv_file.close();
}

// �ǂݍ��񂾒n�`�f�[�^���擾���s��
std::vector<std::vector<int>> CTerrainLoader::GetTerrainData()
{
	if (map_info.empty())
	{
		MessageBoxA(NULL, "�n�`�f�[�^���ǂݍ��܂�Ă��Ȃ����Acsv�t�@�C�����Ƀf�[�^������܂���", "�G���[", MB_OK | MB_ICONERROR);
	}
	return map_info;
}

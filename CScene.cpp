#include "CScene.h"

// static�����o�ϐ����`
std::vector<std::vector<int>> CScene::map_data;
std::list<CGameObject*> CScene::map_object;
ID3D11Buffer* CScene::vertexBufferMap;

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::CreateStage(TERRAIN_ID _id, CCamera* _useCamera)
{
	// �}�b�v�f�[�^��csv�t�@�C���̓ǂݍ���
	CTerrainLoader::GetInstance()->LoadTerrainData(_id);
	map_data = CTerrainLoader::GetInstance()->GetTerrainData();
	
	// ��ʍ�������_�Ƃ����A�n�߂̃^�C���̈ʒu��ݒ�
	float x_tile = ORIGIN_TILE_POS_X;
	float y_tile = ORIGIN_TILE_POS_Y;

	// �c�������[�v
	for (int i = 0; i < map_data.size(); i++)
	{
		// y�����̃^�C����u���ʒu������
		y_tile = ORIGIN_TILE_POS_Y - (TILE_HEIGHT * i);

		// ���������[�v
		for (int j = 0; j < map_data[i].size(); j++)
		{
			// x�����̃^�C����u���ʒu������
			x_tile = ORIGIN_TILE_POS_X + (TILE_WIDTH * j);

			// �ǂݍ��܂ꂽ�f�[�^��1�Ȃ�}�b�v�^�C��������
			if (map_data[i][j] == 1)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO)));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
			}
		}

		// ���̍s�ֈړ�����̂�x���������ɖ߂�
		x_tile = ORIGIN_TILE_POS_X;
	}

}

void CScene::DestroyStage()
{
	// map_data������ς݂łȂ��Ȃ����������s��
	if (!map_data.empty())
	{
		// ���X�g�ɓo�^���ꂽ�I�u�W�F�N�g�̉��
		for (auto it = map_object.begin(); it != map_object.end(); it++)
		{
			delete(*it);
		}
		// �I�u�W�F�N�g�̃��X�g���N���A����
		map_object.clear();
	}

	// �}�b�v�p���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferMap);
}

void CScene::Update()
{
}

void CScene::Draw()
{
	// ���X�g�ɓo�^���ꂽ�I�u�W�F�N�g�̕`��
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		(*it)->Draw();
	}
}

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
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::BLOCK)));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT};
			}
			// �X�P���g���^�C��
			if (map_data[i][j] == 50)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CGameObject(vertexBufferMap, NULL, {1.0f, 1.0f}, OBJECT_TYPE::SKELETON_TILE));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// �ʏ핁�ʂ̃^�C��(�͗l����)
			if (map_data[i][j] == 11)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::NOMAL_TILE)));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// �����^�C��
			if (map_data[i][j] == 12)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::darkTile)));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// �G
			if (map_data[i][j] == 66)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CEnemy(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY), { 0.333333f ,0.5f }, OBJECT_TYPE::ENEMY));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				map_object.back()->transform.position.z = -0.1f;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	�����N����I�u�W�F�N�g�����i�E�����j
			if (map_data[i][j] == 2)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_RIGHT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_RIGHT));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_RIGHT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;

				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	�E������@
			if (map_data[i][j] == 22)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::Senpuuki), { 0.5f ,0.333333f }, OBJECT_TYPE::WIND_RIGHT));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 2, 3, ANIM_PATTERN::WIND_RIGHT, 0.3f);

				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	�����N����I�u�W�F�N�g�����i�E�����j(�󒆁j
			if (map_data[i][j] == 30)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_RIGHT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_RIGHTS));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_RIGHT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;
			}

			//	�����N����I�u�W�F�N�g�����i������j
			if (map_data[i][j] == 3)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_UP), { 1.0f, 0.2f }, OBJECT_TYPE::WIND_UP));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 1, 5, ANIM_PATTERN::WIND_ANIM_UP_LEFT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;

				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// �������@
			if (map_data[i][j] == 33)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::Senpuuki), { 0.5f ,0.3333333f }, OBJECT_TYPE::WIND_UP));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 2, 3, ANIM_PATTERN::WIND_UP, 0.3f);

				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}

			// �_���[�W�^�C��
			if (map_data[i][j] == 4)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new Cdamagetile(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::DTILEX), { 1.0f, 1.0f }, OBJECT_TYPE::DAMAGE_TILE));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			if (map_data[i][j] == 25)	//�������̉�e
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new Cdamagetile(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::DTILE_DOWN), { 1.0f, 1.0f }, OBJECT_TYPE::DAMAGE_DOWN));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			if (map_data[i][j] == 20)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new Cdamagetile(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TILE), { 1.0f, 1.0f }, OBJECT_TYPE::DAMAGE_TILEY));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			//	�����N����I�u�W�F�N�g�����i�������j
			if (map_data[i][j] == 9)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_LEFT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_LEFT));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_UP_LEFT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;

				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}
			// ��������@
			if (map_data[i][j] == 80)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::Senpuuki), { 0.5f ,0.333333f }, OBJECT_TYPE::WIND_LEFT));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 2, 3, ANIM_PATTERN::WIND_LEFT, 0.3f);

				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };
			}

			if (map_data[i][j] == 40)
			{
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CWind(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::WIND_LEFT), { 0.2f, 1.0f }, OBJECT_TYPE::WIND_LEFTS));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT };

				//	�A�j���[�V����������
				map_object.back()->InitAnimParameter(true, 5, 1, ANIM_PATTERN::WIND_ANIM_UP_LEFT, 0.15f);
				map_object.back()->materialDiffuse.w = 0.5f;
			}
			// �S�[��
			if (map_data[i][j] == 99)
			{
				// ���S�[�������傫����ύX���Ă��܂�
				// �}�b�v�^�C����1��new����
				map_object.push_back(new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::HATA), { 1.0f, 1.0f }, OBJECT_TYPE::GOAL));
				// �g���J������ݒ�
				map_object.back()->SetUseingCamera(_useCamera);
				// �^�C���̃T�C�Y���Z�b�g����
				map_object.back()->transform.scale.x = map_object.back()->transform.scale.x * TILE_WIDTH * 1.5;
				map_object.back()->transform.scale.y = map_object.back()->transform.scale.y * TILE_HEIGHT * 2.5;
				// �^�C���̈ʒu���Z�b�g����
				map_object.back()->transform.position.x = x_tile;
				map_object.back()->transform.position.y = y_tile + 0.11f;
				// �R���C�_�[�̐ݒ�
				map_object.back()->Bcol = { x_tile, y_tile, TILE_WIDTH, TILE_HEIGHT * 2};
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

void CScene::DrawTerrain()
{
	// �n�`�I�u�W�F�N�g�̕`��
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		// �����^�C���͕`�悵�Ȃ�
		// �G�͌�ŕ`�悷��
		if ((*it)->GetObjectType() != OBJECT_TYPE::SKELETON_TILE &&
			(*it)->GetObjectType() != OBJECT_TYPE::ENEMY)
		{
			(*it)->Draw();
		}
	}
	// �G�̕`��
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		if ((*it)->GetObjectType() == OBJECT_TYPE::ENEMY)
		{
			(*it)->Draw();
		}
	}
}

void CScene::UpdateTerrain()
{
	// �n�`�I�u�W�F�N�g�̕`��
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		(*it)->Update();
	}
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

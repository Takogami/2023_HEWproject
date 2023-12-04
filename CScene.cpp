#include "CScene.h"
#include "ResultScene.h"

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
				map_object.push_back( new CGameObject(vertexBufferMap, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO)) );
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

void CScene::CorrectPosition(CPlayer* moveObject, CGameObject* holdObject)
{
	float overlapX = moveObject->Bcol.sizeX / 2 + holdObject->Bcol.sizeX / 2 - std::abs(moveObject->Bcol.centerX - holdObject->Bcol.centerX);
	float overlapY = moveObject->Bcol.sizeY / 2 + holdObject->Bcol.sizeY / 2 - std::abs(moveObject->Bcol.centerY - holdObject->Bcol.centerY);

	if (overlapX < overlapY)
	{
		// X�������ɂ߂荞��ł���ꍇ
		if (moveObject->Bcol.centerX < holdObject->Bcol.centerX)
		{
			moveObject->Bcol.centerX -= overlapX;
			//�R���C�_�[�̒��S�_�ƃI�u�W�F�N�g�̒��S�_��A��������
			moveObject->transform.position.x = moveObject->Bcol.centerX;
		}
		else
		{
			moveObject->Bcol.centerX += overlapX;
			//�R���C�_�[�̒��S�_�ƃI�u�W�F�N�g�̒��S�_��A��������
			moveObject->transform.position.x = moveObject->Bcol.centerX;
		}
	}
	else{
		// Y�������ɂ߂荞��ł���ꍇ
		if (moveObject->Bcol.centerY < holdObject->Bcol.centerY)
		{
			moveObject->Bcol.centerY -= overlapY;
			//�R���C�_�[�̒��S�_�ƃI�u�W�F�N�g�̒��S�_��A��������
			moveObject->transform.position.y = moveObject->Bcol.centerY;
		}
		else
		{
			moveObject->Bcol.centerY += overlapY;
			//�R���C�_�[�̒��S�_�ƃI�u�W�F�N�g�̒��S�_��A��������
			moveObject->transform.position.y = moveObject->Bcol.centerY;
		}

		//�R���C�_�[�̒��S�_�ƃI�u�W�F�N�g�̒��S�_��A��������
		moveObject->transform.position.x = moveObject->Bcol.centerX;
		moveObject->transform.position.y = moveObject->Bcol.centerY;
	}
}

bool CScene::TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2)
{
	// ���S�_�Ԃ̋���
	float distanceX = std::abs(obj1.centerX - obj2.centerX);
	float distanceY = std::abs(obj1.centerY - obj2.centerY);

	// ���S�_�Ԃ̋��������ꂼ��̋�`�̕��ƍ����̔����𑫂������̂�菬�����ꍇ�A�d�Ȃ��Ă���Ɣ���
	if (distanceX < (obj1.sizeX / 2 + obj2.sizeX / 2) && distanceY < (obj1.sizeY / 2 + obj2.sizeY / 2))
	{
		return true;
	}

	return false;
}

void CScene::DrawTerrain()
{
	// �n�`�I�u�W�F�N�g�̕`��
	for (auto it = map_object.begin(); it != map_object.end(); it++)
	{
		(*it)->Draw();
	}
}

void CScene::Update()
{
}

void CScene::Draw()
{
}

#pragma once

/* �C���N���[�h */
#include <list>
#include "CPlayer.h"
#include "CCursor.h"
#include "CWind.h"
#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CTextureLoader.h"
#include "CInput.h"
#include "CDrawString.h"
#include "CEase.h"
#include "CTimer.h"
#include "CEnemy.h"

class CScene
{
private:
	// �}�b�v�f�[�^�Ɋ֘A����ϐ��Q
	// �S�ẴV�[���ŋ��L���邽�߁Astatic���g�p����
	// �}�b�v�f�[�^���󂯎��2�����ϒ��z��
	static std::vector<std::vector<int>> map_data;
	// �}�b�v�I�u�W�F�N�g�p�̒��_�o�b�t�@
	static ID3D11Buffer* vertexBufferMap;

	static ID3D11Buffer* vertexBufferEnemy;

	CEnemy* enemy;

	CCamera* Cam;

	// �g���I�u�W�F�N�g�̃��X�g
	// �܂Ƃ߂�Update��Draw���s�����߂Ɏg�p
	std::list<CGameObject*>Objects;

public:
	/* �����o�ϐ� */
	// �}�b�v�I�u�W�F�N�g�p�̃��X�g
	static std::list<CGameObject*> map_object;

	/* ���\�b�h */

	// �R���X�g���N�^
	CScene();
	// �f�X�X�g���N�^
	virtual ~CScene();

	// �ǂݍ��񂾒n�`���ŃX�e�[�W�𐶐�����
	void CreateStage(TERRAIN_ID _id, CCamera* _useCamera);

	// �X�e�[�W�̌�Еt��(�e�I�u�W�F�N�g�̉���Ȃ�)
	static void DestroyStage();

	// �X�e�[�W�̕`��݂̂��s��
	void DrawTerrain();

	//�G�̍X�V
	void EnemyUpdate();

	//�G�̕`��
	void EnemyDraw();

	// �I�[�o�[���C�h����p�̊֐�
	// �V�[���̍X�V����
	virtual void Update();
	// �`��
	virtual void Draw();
};


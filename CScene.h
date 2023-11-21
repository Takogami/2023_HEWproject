#pragma once

/* �C���N���[�h */
#include <list>
#include "CGameObject.h"
#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CTextureLoader.h"
#include "CInput.h"

class CScene
{
private:

protected:
	// �}�b�v�f�[�^�Ɋ֘A����ϐ��Q
	// �S�ẴV�[���ŋ��L���邽�߁Astatic
	// �}�b�v�f�[�^���󂯎��2�����ϒ��z��
	static std::vector<std::vector<int>> map_data;
	// �}�b�v�\���Ɋ֘A����
	static std::list<CGameObject*> map_object;

public:
	/* ���\�b�h */

	// �R���X�g���N�^
	CScene();
	// �f�X�X�g���N�^
	virtual ~CScene();

	// �ǂݍ��񂾒n�`���ŃX�e�[�W�𐶐�����
	void CreateStage(TERRAIN_ID id);

	// �X�e�[�W�̌�Еt��(�e�I�u�W�F�N�g�̉���Ȃ�)
	void DestroyStage();

	// �I�[�o�[���C�h����p�̊֐�
	// �V�[���̍X�V����
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
};


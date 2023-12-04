#pragma once

/* �C���N���[�h */
#include <list>
#include "CPlayer.h"
#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CTextureLoader.h"
#include "CInput.h"

class CScene
{
private:
	// �}�b�v�f�[�^�Ɋ֘A����ϐ��Q
	// �S�ẴV�[���ŋ��L���邽�߁Astatic���g�p����
	// �}�b�v�f�[�^���󂯎��2�����ϒ��z��
	static std::vector<std::vector<int>> map_data;
	// �}�b�v�I�u�W�F�N�g�p�̒��_�o�b�t�@
	static ID3D11Buffer* vertexBufferMap;

protected:
	// �}�b�v�I�u�W�F�N�g�p�̃��X�g
	static std::list<CGameObject*> map_object;

public:
	/* ���\�b�h */

	// �R���X�g���N�^
	CScene();
	// �f�X�X�g���N�^
	virtual ~CScene();

	// �ǂݍ��񂾒n�`���ŃX�e�[�W�𐶐�����
	void CreateStage(TERRAIN_ID _id, CCamera* _useCamera);

	// �X�e�[�W�̌�Еt��(�e�I�u�W�F�N�g�̉���Ȃ�)
	void DestroyStage();

	// �l�p�`���m�̓����蔻��
	static bool TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2);
	// �ʒu�␳
	static void CorrectPosition(CPlayer* moveObject, CGameObject* holdObject);

	// �X�e�[�W�̕`��݂̂��s��
	void DrawTerrain();

	// �I�[�o�[���C�h����p�̊֐�
	// �V�[���̍X�V����
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
};


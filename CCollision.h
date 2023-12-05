#pragma once

// BoxCollider�^�̒�`
struct BoxCollider
{
	float centerX;	// Box�R���C�_�[�̒��S�_X
	float centerY;	// Box�R���C�_�[�̒��S�_Y
	float sizeX;	// Box�R���C�_�[��x�����̑傫��
	float sizeY;	// Box�R���C�_�[��y�����̑傫��
};

class CCollision
{
public:

	/* ���\�b�h */

	// �l�p�`���m�̓����蔻��
	static bool TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2);
	// �ʒu�␳
	static void CorrectPosition(BoxCollider& obj1, BoxCollider& obj2);

};


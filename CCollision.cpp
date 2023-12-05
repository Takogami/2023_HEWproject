#include "CCollision.h"
#include <cmath>

void CCollision::CorrectPosition(BoxCollider& obj1, BoxCollider& obj2)
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
	else {
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

bool CCollision::TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2)
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

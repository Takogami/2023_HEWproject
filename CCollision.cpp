#include "CCollision.h"
#include <cmath>

CORRECT_DIR CCollision::CorrectPosition(BoxCollider& moveObject, BoxCollider& holdObject)
{
	// x,y���ꂼ��߂荞��ł��钷�����v�Z
	float overlapX = ((moveObject.sizeX / 2) + (holdObject.sizeX / 2)) - std::abs(moveObject.centerX - holdObject.centerX);
	float overlapY = ((moveObject.sizeY / 2) + (holdObject.sizeY / 2)) - std::abs(moveObject.centerY - holdObject.centerY);
	// �␳�����������i�[����CORRECT_DIR�^�ϐ�
	CORRECT_DIR correct_dir = { 0 };


	// �R���C�_�[��␳����
	if (overlapY < overlapX)
	{
		// Y�������ɂ߂荞��ł���ꍇ
		if (moveObject.centerY < holdObject.centerY)
		{
			moveObject.centerY -= overlapY;
			correct_dir.y = -1;
		}
		else
		{
			moveObject.centerY += overlapY;
			correct_dir.y = 1;
		}

	}
	//�{���̂߂荞�݌v�Z�̕␳�Ə����Ⴄ�̂�0.002�����{���Ă�����
	else if ((overlapX + 0.002f) < overlapY) {
		// X�������ɂ߂荞��ł���ꍇ
		if (moveObject.centerX < holdObject.centerX)
		{
			moveObject.centerX -= overlapX;
			correct_dir.x = -1;
		}
		else if (moveObject.centerX > holdObject.centerX)
		{
			moveObject.centerX += overlapX;
			correct_dir.x = 1;
		}
	}

	 //�␳����������Ԃ�
	return correct_dir;
}

CORRECT_DIR CCollision::CCollision::DtestCorrectPosition(BoxCollider& moveObject, BoxCollider& holdObject)
{
	// x,y���ꂼ��߂荞��ł��钷�����v�Z
	float overlapX = ((moveObject.sizeX / 2) + (holdObject.sizeX / 2)) - std::abs(moveObject.centerX - holdObject.centerX);
	float overlapY = ((moveObject.sizeY / 2) + (holdObject.sizeY / 2)) - std::abs(moveObject.centerY - holdObject.centerY);
	// �␳�����������i�[����CORRECT_DIR�^�ϐ�
	CORRECT_DIR correct_dir = { 0 };

	bool XRflg = false;
	bool XLflg = false;

	// �R���C�_�[��␳����
		// �R���C�_�[��␳����
	if (overlapY < overlapX)
	{
		// Y�������ɂ߂荞��ł���ꍇ
		if (moveObject.centerY < holdObject.centerY)
		{
			moveObject.centerY -= overlapY;
			moveObject.centerX -= 0.2f;
			correct_dir.y = -1;
		}
		else
		{
			moveObject.centerY += overlapY;
			correct_dir.y = 1;
		}

	}
	//�{���̂߂荞�݌v�Z�̕␳�Ə����Ⴄ�̂�0.002�����{���Ă�����
	else if ((overlapX + 0.002f) < overlapY) {
		// X�������ɂ߂荞��ł���ꍇ
		if (moveObject.centerX < holdObject.centerX)
		{
			moveObject.centerX -= overlapX;
			correct_dir.x = -1;
		}
		else if (moveObject.centerX > holdObject.centerX)
		{
			moveObject.centerX += overlapX;
			correct_dir.x = 1;
		}
	}

	//�␳����������Ԃ�
	return correct_dir;
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

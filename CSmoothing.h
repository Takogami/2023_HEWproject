#pragma once
class CSmoothing
{
private:
	// �X���[�W���O�W��
	float alpha;
	// �Ǐ]�Ώۂ̍��W
	float* posT;
	// �ύX������W
	float* posF;

public:
	// �R���X�g���N�^
	CSmoothing();
	// �f�X�g���N�^
	~CSmoothing();
	// �X�V
	void Update();
	// �X���[�W���O������
	// ����1:�Ǐ]�Ώۂ̍��W ����2:�ύX������W ����3:�X���[�Y�W��(0�`1)
	void InitSmooth(float* target_pos,float* follow_pos, float coef);
	// �X���[�W���O�W���̕ύX
	void ChangeSmoothCoef(float coef);
};


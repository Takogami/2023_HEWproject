#pragma once
#include "CPlayer.h"

class CWind :
    public CGameObject
{
private:
    // ���̋���(�����l : 0.01f)
    float windStrength = 0.01f;
    float windStrengthY = 0.02f;

public:
    // �R���X�g���N�^
    CWind(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
    // �f�X�g���N�^
    ~CWind() override;

    // �X�V
    void Update() override;
    // ���̋�����ݒ�
    void SetWindStrangth(float power);
    // ���̋�����Ԃ�
    float GetWindStrength() { return windStrength; }

    float GetWindStrengthY() { return windStrengthY; };
};


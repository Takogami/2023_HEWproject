#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
    /* �����o�ϐ� */

public:
    /* �����o�ϐ� */

    // �����x�N�g��
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* ���\�b�h */

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv);
    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


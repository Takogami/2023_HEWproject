#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
    /* �����o�ϐ� */

private:
    // �ړ����x
    float moveSpeed;
    // �O�t���[�����ꂽ�Փ˕␳�̕���
    CORRECT_DIR prevFrameCorrect = { 0 };
    // �O�t���[���̕���
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, 0.0f, 0.0f };

    /* ���\�b�h */
    void Input();   // 
    void Jump();    // 


public:
    /* �����o�ϐ� */

    // �����x�N�g��
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* ���\�b�h */

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv);
    // �ړ����x��ݒ�
    inline void SetMoveSpeed(float sp) { moveSpeed = sp; };
    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


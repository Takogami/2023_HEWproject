#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
private:
    /* �����o�ϐ� */

    // �d��
    const float gravity = 0.97f / 200;
    // �W�����v�J�n��(�������)�̃W�����v�̋���
    const float ini_jumpStrength = 13.0f / 200;
    // ���݂̃W�����v�̋���
    float jumpStrength = ini_jumpStrength;
    // �W�����v�t���O
    bool isJump = false;

    // �ړ����x
    DirectX::XMFLOAT2 velocity;

    // �O�t���[�����ꂽ�Փ˕␳�̕���
    CORRECT_DIR prevFrameCorrect = { 0 };
    // �O�t���[���̕���
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };

    /* ���\�b�h */

    void PlayerInput(); // ���͏���
    float Jump();       // �W�����v�͂�Ԃ�

public:
    /* �����o�ϐ� */

    // �����x�N�g��
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* ���\�b�h */

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv);
    // �ړ����x��ݒ�
    inline void SetMoveSpeed(float sp) { velocity.x = sp; };

    //  ���̏����i�������j
    void Wind();

    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


#pragma once
#include "CGameObject.h"

enum class EState
{
    NORMAL,
    LEFTWALK,
    RIGHTWALK,
};

class CEnemy :
    public CGameObject
{
private:
    // �d��
    const float gravity = 0.97f / 200;
    // ���x�̌��E�l
    const float velocityY_limit = 0.0005f;
    // �O�t���[�����ꂽ�Փ˕␳�̕���
    CORRECT_DIR prevFrameCorrect = { 0 };
    // �O�t���[���̕���
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };

    EState State = EState::NORMAL;

    void EnemyPattern();

public:
    /* �����o�ϐ� */

    // �ړ����x
    DirectX::XMFLOAT2 velocity;

    // �����x�N�g��
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    // �󂯂Ă��镗�̕����x�N�g��
    DirectX::XMFLOAT3 dir_wind = { 0.0f, 0.0f, 0.0f };
    // �󂯂Ă��镗��
    float windStrength = 0.0f;
    /* ���\�b�h */

    CEnemy(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
    // �ړ����x��ݒ�
    inline void SetMoveSpeed(float sp) { velocity.x = sp; };

    EState GetState();
    void SetState(EState state);

    void Update() override;
    void Draw() override;
    ~CEnemy() override;
};


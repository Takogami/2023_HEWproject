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
    // 重力
    const float gravity = 0.97f / 200;
    // 速度の限界値
    const float velocityY_limit = 0.0005f;
    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    // 前フレームの方向
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };

    EState State = EState::NORMAL;

    void EnemyPattern();

public:
    /* メンバ変数 */

    // 移動速度
    DirectX::XMFLOAT2 velocity;

    // 方向ベクトル
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    // 受けている風の方向ベクトル
    DirectX::XMFLOAT3 dir_wind = { 0.0f, 0.0f, 0.0f };
    // 受けている風力
    float windStrength = 0.0f;
    /* メソッド */

    CEnemy(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
    // 移動速度を設定
    inline void SetMoveSpeed(float sp) { velocity.x = sp; };

    EState GetState();
    void SetState(EState state);

    void Update() override;
    void Draw() override;
    ~CEnemy() override;
};


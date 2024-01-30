#pragma once
#include "CGameObject.h"
#include "CTimer.h"

enum class PState
{
    NORMAL,
    FALL,
    BREAKLEFT,
    BREAKRIGHT,
};

class CPlayer :
    public CGameObject
{
private:
    /* メンバ変数 */

    // 重力
    const float gravity = 0.97f / 200;
    // ジャンプ開始時(初期状態)のジャンプの強さ
    const float ini_jumpStrength = 13.0f / 200;
    // 速度の限界値
    const float velocityY_limit = 0.0005f;

    // 現在のジャンプの強さ
    float jumpStrength = ini_jumpStrength;
    // ジャンプフラグ
    bool isJump = false;

    PState State = PState::NORMAL;

    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    // 前フレームの方向
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };

    /* メソッド */

    void PlayerInput(); // 入力処理
    float Jump();       // ジャンプ力を返す

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

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type = OBJECT_TYPE::PLAYER);
    // 移動速度を設定
    inline void SetMoveSpeed(float sp) { velocity.x = sp; };

    PState GetState();
    void SetState(PState state);

    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


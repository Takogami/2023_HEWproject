#pragma once
#include "CGameObject.h"
#include "CAnimation.h"

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

    // スティック入力一時保存用
    float input_stickX;
    float input_stickY;
    float old_input_stickX = 0.0f;
    float old_input_stickY = 0.0f;

    // 重力
    const float gravity = 0.97f / 200;
    // ジャンプ開始時(初期状態)のジャンプの強さ
    const float ini_jumpStrength = 13.0f / 200;
    // 現在のジャンプの強さ
    float jumpStrength = ini_jumpStrength;
    // ジャンプフラグ
    bool isJump = false;

    // アニメーションフラグ
    bool isanimation = false;

    PState State = PState::NORMAL;

    // 移動速度
    DirectX::XMFLOAT2 velocity;

    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    // 前フレームの方向
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };

    /* メソッド */

    void PlayerInput(); // 入力処理
    float Jump();       // ジャンプ力を返す

public:
    /* メンバ変数 */

    // 方向ベクトル
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* メソッド */

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type = OBJECT_TYPE::PLAYER);
    // 移動速度を設定
    inline void SetMoveSpeed(float sp) { velocity.x = sp; };

    //  風の処理（お試し）
    void Wind();

    PState GetState();
    void SetState(PState state);

    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


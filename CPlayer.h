﻿#pragma once
#include "CGameObject.h"

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
    const float ini_jumpStrength = 10.0f / 500;
    // 速度の限界値
    const float velocityY_limit = 0.0005f;
    // 現在のジャンプの強さ
    float jumpStrength = ini_jumpStrength;
    // ジャンプフラグ
    bool isJump = false;
    // アニメーションフラグ
    bool isanimation = false;

    // プレイヤーの状態
    PState State = PState::NORMAL;

    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    // 前フレームの方向
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };

public:
    /* メンバ変数 */
    // 移動速度
    DirectX::XMFLOAT2 velocity;
    // 方向ベクトル
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    // 受けている風の方向ベクトル
    DirectX::XMFLOAT3 dir_wind = { 0.0f, 0.0f, 0.0f };

    // ダメージを受けた時の方向ベクトル
    DirectX::XMFLOAT3 Ddir = { 0,0,0 };

    // 受けている風力
    FLOAT_XY receiveWindPower = { 0.0f, 0.0f };

    //吹っ飛ぶ力
    float Sumash = 0.0f;



    /* メソッド */

    // 入力処理
    void PlayerInput();
    // ジャンプ力を返す
    float Jump();
    // 風を受けたときの処理
    void ReceiveWind();
    
    void Rknoc(DirectX::XMFLOAT3);
    void Lknoc(DirectX::XMFLOAT3);

public:
    /* メソッド */

    // コンストラクタ
    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type = OBJECT_TYPE::PLAYER);
    // 移動速度を設定
    inline void SetMoveSpeed(float sp) { velocity.x = sp; };

    // 状態の取得
    PState GetState();
    // 状態の設定
    void SetState(PState state);

    // 更新
    void Update() override;
    // 描画
    void Draw() override;

    // デストラクタ
    ~CPlayer() override;

};


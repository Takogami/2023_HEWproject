#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
    /* メンバ変数 */

private:
    // 移動速度
    float moveSpeed;
    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    // 前フレームの方向
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, 0.0f, 0.0f };

    /* メソッド */
    void Input();   // 
    void Jump();    // 


public:
    /* メンバ変数 */

    // 方向ベクトル
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* メソッド */

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv);
    // 移動速度を設定
    inline void SetMoveSpeed(float sp) { moveSpeed = sp; };
    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


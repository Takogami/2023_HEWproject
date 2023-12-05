#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
    /* メンバ変数 */

public:
    /* メンバ変数 */

    // 方向ベクトル
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* メソッド */

    CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv);
    void Update() override;
    void Draw() override;
    ~CPlayer() override;
};


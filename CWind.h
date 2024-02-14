#pragma once
#include "CPlayer.h"

class CWind :
    public CGameObject
{
private:
    // 風の強さ(初期値 : 0.01f)
    float windStrength = 0.01f;
    float windStrengthY = 0.02f;

public:
    // コンストラクタ
    CWind(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
    // デストラクタ
    ~CWind() override;

    // 更新
    void Update() override;
    // 風の強さを設定
    void SetWindStrangth(float power);
    // 風の強さを返す
    float GetWindStrength() { return windStrength; }

    float GetWindStrengthY() { return windStrengthY; };
};


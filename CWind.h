#pragma once
#include "CPlayer.h"

class CWind :
    public CGameObject
{
private:

public:

    CWind(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
    ~CWind();   //  デストラクタ

    //  更新
    void Update();
};


#pragma once
#include "CPlayer.h"

class CWind
{
private:

public:

    CWind();    //  コンストラクタ
    ~CWind();   //  デストラクタ

    //  更新
    void Update();

    //  右向きの風（引数：）
    void Wind_Right(CPlayer* palyerStatus, float windPower);
};


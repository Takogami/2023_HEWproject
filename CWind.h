#pragma once
#include "CPlayer.h"

class CWind
{
private:

public:

    CWind();    //  �R���X�g���N�^
    ~CWind();   //  �f�X�g���N�^

    //  �X�V
    void Update();

    //  �E�����̕��i�����F�j
    void Wind_Right(CPlayer* palyerStatus, float windPower);
};


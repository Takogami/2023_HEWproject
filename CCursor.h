#pragma once
#include "CGameObject.h"

//タイトルからシーン移動できる数
#define SCENE_COUNT 3

//タイトルのカーソルの位置の列挙型
enum class CCursor_Point
{
    STAGE,
    OPTION,
    EXIT,
};

class CCursor :
    public CGameObject
{
private:
    /* メンバ変数 */

    int scene_count;


public:
    /* メンバ変数 */

    // 方向ベクトル
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* メソッド */

    CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex);
    void Update() override;
    void Draw() override;
    CCursor_Point GetCursorPoint()const;
    ~CCursor() override;
};

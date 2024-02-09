#pragma once
#include "CGameObject.h"

//タイトルからシーン移動できる数
#define SCENE_COUNT 3

class CEase;

//タイトルのカーソルの位置の列挙型
enum class CCursor_Point
{
    STAGE,
    OPTION,
    EXIT,
};

//別名で関連付ける
enum class CCursor_PointResult
{
    RETRY = (int)CCursor_Point::STAGE,
    SELECT = (int)CCursor_Point::OPTION,
    TITLE = (int)CCursor_Point::EXIT,
};

class CCursor :
    public CGameObject
{
private:
    /* メンバ変数 */

    int scene_count = 0;

    // 初期位置
    FLOAT_XY ini_position = { 0.0f, 0.0f };
    // カーソルの動く距離
    float moveDistance = 0.3f;
    // カーソルのイージング
    CEase* curEase;
    bool curReturn = false;

public:
    /* メソッド */

    CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv ={ 1.0f ,1.0f }, OBJECT_TYPE type = OBJECT_TYPE::NORMAL);
    void CursorInput();
    void Update() override;
    void Draw() override;

    // カーソルの初期化
    // 引数1 : 初期位置 引数2 : 動く距離
    void Init(FLOAT_XY ini_pos, float move = 0.3f);

    //タイトル画面でのポイント位置を取得
    CCursor_Point GetCursorPoint()const;

    ~CCursor() override;
};

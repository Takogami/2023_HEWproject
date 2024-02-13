#pragma once
#include "CGameObject.h"

class CEase;

//リザルトシーンのカーソル
enum class CCursor_PointResult
{
    RETRY,
    SELECT,
    TITLE,
    INACTIVE,
};

//別名で関連付ける
enum class CCursor_Point
{
    STAGE = (int)CCursor_PointResult::RETRY,
    EXIT = (int)CCursor_PointResult::SELECT,
    INACTIVE,
};

//別名で関連付ける
enum class CCursor_PointClear
{
    SELECT = (int)CCursor_PointResult::RETRY,
    TITLE = (int)CCursor_PointResult::SELECT,
    INACTIVE,
};

class CCursor :
    public CGameObject
{
private:
    /* メンバ変数 */

    int scene_count = 0;

    // 遷移できるシーン数
    int sceneNum = 3;

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
    // 引数1 : 初期位置 引数2 : 遷移できるシーン数 引数3 : 動く距離
    void Init(FLOAT_XY ini_pos, int scene = 3, float move = 0.3f);

    //タイトル画面でのポイント位置を取得
    CCursor_Point GetCursorPoint()const;

    ~CCursor() override;
};

#pragma once
#include "CGameObject.h"

/* 前方宣言 */
class CEase;
class CSmoothing;

enum class PState
{
    NORMAL,
    FALL,
    BREAKLEFT,
    BREAKRIGHT,
    CLEAR_GAMEOVER, // クリア、ゲームオーバー状態
};

class CPlayer :
    public CGameObject
{
private:
    /* メンバ変数 */

    // スティック入力一時保存用
    float input_stickX;
    float input_stickY;
    float input_stickX2;
    float input_stickY2;
    float old_input_stickX = 0.0f;
    float old_input_stickY = 0.0f;
    float old_input_stickX2 = 0.0f;
    float old_input_stickY2 = 0.0f;

    // プレイヤーのダメージエフェクト
    CGameObject* damageEffect;

    // ゲームオーバー背景
    CGameObject* gameoverBg;
    // プレイヤーの拡大率
    float gameoverPlayerUpperSize = 1.0f;
    // スケールの初期値
    DirectX::XMFLOAT3 ini_scale;
    // ゲームオーバー時のプレイヤー位置を戻すイージング
    CEase* gameoverEaseX;
    CEase* gameoverEaseY;

    // プレイヤーのダメージエフェクト用頂点バッファ
    ID3D11Buffer* vertexBufferEffect;

    // 重力
    const float gravity = 0.97f / 200;
    // ジャンプ開始時(初期状態)のジャンプの強さ
    const float ini_jumpStrength = 10.0f / 450;
    // 速度の限界値
    const float velocityY_limit = 0.0005f;
    // 現在のジャンプの強さ
    float jumpStrength = ini_jumpStrength;
    // ジャンプフラグ
    bool isJump = false;
    // アニメーションフラグ
    bool isanimation = false;

    //  風を受けるフラグ
    bool isWindRight = false;   //  右向き
    bool isWindLeft = false;    //  左向き
    bool isWindUp = false;      //  上向き

    //  フライアニメーション制御カウント
    int FlyCount = 0;

    // 吹っ飛びのスムージング
    CSmoothing* smoothing;

    bool nockf = false;
    bool nockT = false;
    bool Aflame = false;
    bool HitTy = false;
    float moveF = 0.0f;
    float flameCounter = 0.0f;
    float flameCounterMK2 = 0.0f;
    int AflameCounter = 0.0f;
    
    // プレイヤーの状態
    PState State = PState::NORMAL;

    // 前フレームされた衝突補正の方向
    CORRECT_DIR prevFrameCorrect = { 0 };
    CORRECT_DIR prevFrameCorrectY = { 0 };
    // 前フレームの方向
    DirectX::XMFLOAT3 prevFrameDir = { 0.0f, -1.0f, 0.0f };
    // 最後に横入力された向き
    DirectX::XMFLOAT3 FInput_dir = { 1.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 RFInput_dir = { 0.0f, 0.0f , 0.0f };

    int jumpCount = 0;

    bool test = false;

    //  アニメーションお試し
    bool fly = false;

    // クリアフラグ
    bool clearFlg = false;
    // ゲームオーバーフラグ
    bool gameOverFlg = false;
    // リザルトに遷移するまでの時間を測る
    int ResultShiftCount = 0;

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

    /* メソッド */

    // 入力処理
    void PlayerInput();
    // ジャンプ力を返す
    float Jump();
    // 風を受けたときの処理
    void ReceiveWind();

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

    // コントローラーのインデックス（0〜3）
    DWORD controllerIndex = 0;
};


//--------------------------------------------------------------------------
// CGameObject.h
// 
// 作成者:辻 幸宏
// 
// 概要:基本ゲームオブジェクトクラスを生成するクラス
//      基底クラスとして使用することを推奨
//      セットでCTransformクラスを使用すること
// 
//      10/24:カメラに対応
//            SetUsingCamera()で使用するカメラの設定
// 
// 最終更新日時:2023/10/24
//--------------------------------------------------------------------------

#pragma once

/* インクルード */
#include "direct3d.h"
#include "CTransform.h"
#include "CCollision.h"
#include "CAnimation.h"

/* CCameraクラスの前方宣言 */
class CCamera;

//CGameObjectクラス
class CGameObject
{
protected:
	/* メンバ変数 */

	ID3D11Buffer* vertexBuffer;			//描画に使用する頂点バッファ
	ID3D11ShaderResourceView* texture;	//テクスチャ変数

	FLOAT_XY uv = { 0.0f,0.0f };		//uv分割移動量(アニメーションに使用)
	FLOAT_XY sprit = { 0.0f,0.0f };		//1コマのサイズ

	CCamera* useCamera;					//描画に使用するカメラのポインタ
	CAnimation* anim;					//アニメーションクラス

public:
	/* メンバ変数 */

	int objectType = 0; // 1: 壁や床, 2: 敵 など
	bool isWind = false;      // 風が吹いているかどうかのフラグ
	float windTime = 0.0f;   // 風が吹く時間
	float windTimer = 0.0f;  // 風のタイマー

	float acceleration = 0.001f;	//	風の強さ
	float deltaTime = 0.01f;	//	1フレームと前のフレームの間に経過した時間の差分

	CTransform transform;								// 仮想世界の中の位置座標,スケール,回転率
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// マテリアル色の設定
	BoxCollider Bcol = { 0.0f, 0.0f, 0.0f, 0.0f };		// Boxコライダーパラメータ

	/* メソッド */

	//初期化処理(コンストラクタ) 引数1:オブジェクトのID 引数2:頂点バッファ 引数3:テクスチャ 引数4:テクスチャ移動量
	//※ 引数3 はuv分割しないなら入力の必要はありません
	CGameObject(int, ID3D11Buffer*, ID3D11ShaderResourceView*, FLOAT_XY uv = { 1.0f,1.0f });
	//終了処理(デストラクタ)
	virtual ~CGameObject();

	//ゲームループごとに実行する処理
	virtual void Update();
	//ゲームループごとに描画する処理
	virtual void Draw();
	//使用するカメラを設定
	void SetUseingCamera(CCamera* setCamera);

	//アニメーションの初期化
	//引数1:初期の再生状態 引数2:横方向の分割数 引数3:初期アニメーションパターン 引数4:初期スピード
	void InitAnimParameter(bool iniPlaying, int spritU, ANIM_PATTERN pattern, float sp);
	// アニメーションのスピードを設定
	void SetAnimationSpeed(float sp);
	// アニメーションのパターンを設定
	void SetAnimationPattern(ANIM_PATTERN pattern);
	// アニメーションの再生
	void PlayAnimation();
	// アニメーションの停止
	void StopAnimation();
	// アニメーションのリセット
	void ResetAnimation();

	//テクスチャの切り抜き
	//引数1:u方向の何番目を切り抜くか  引数2:v方向の何番目を切り抜くか
	void TextureCutout(int u_num, int v_num);

	void SetObjectType(int _objectType);
	int GetObjectType() const;
};


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

/* CCameraクラスの前方宣言 */
class CCamera;

// BoxCollider型の定義
struct BoxCollider
{
	float centerX;	// Boxコライダーの中心点X
	float centerY;	// Boxコライダーの中心点Y
	float sizeX;	// Boxコライダーのx方向の大きさ
	float sizeY;	// Boxコライダーのy方向の大きさ
};

//CGameObjectクラス
class CGameObject
{
protected:
	/* メンバ変数 */

	ID3D11Buffer* vertexBuffer;			//描画に使用する頂点バッファ
	ID3D11ShaderResourceView* texture;	//テクスチャ変数
	FLOAT_XY uv = { 0.0f,0.0f };		//uv分割用(アニメーションに使用)

	CCamera* useCamera;					//描画に使用するカメラのポインタ

public:
	/* メンバ変数 */

	CTransform transform;								//仮想世界の中の位置座標,スケール,回転率
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	//マテリアル色の設定
	BoxCollider Bcol = { 0.0f, 0.0f, 0.0f, 0.0f };		// Boxコライダーパラメータ

	/* メソッド */

	//初期化処理(コンストラクタ) 引数1:頂点バッファ 引数2:テクスチャ 引数3:テクスチャ移動量
	//※ 引数3 はuv分割しないなら入力の必要はありません
	CGameObject(ID3D11Buffer*, ID3D11ShaderResourceView*, FLOAT_XY _uv = { 1.0f,1.0f });
	//終了処理(デストラクタ)
	virtual ~CGameObject();

	//ゲームループごとに実行する処理
	virtual void Update();
	//ゲームループごとに描画する処理
	virtual void Draw();

	//マテリアル色セット用関数
	void SetMaterial(DirectX::XMFLOAT4 material) { materialDiffuse = material; };
	//使用するカメラを設定
	void SetUseingCamera(CCamera* setCamera);
};


//--------------------------------------------------------------------------
// CGameObject.cpp
// 
// 作成者:辻 幸宏
// 
// 概要:基本ゲームオブジェクトクラスを生成するクラス
//      このファイルではメソッドの本体を記述している
//      基底クラスとして使用することを推奨
//      セットでCTransformクラスをインクルードすること
// 
//       10/24:カメラに対応
//             SetUsingCamera()で使用するカメラの設定
// 
// 最終更新日時:2023/10/24
//--------------------------------------------------------------------------

/* インクルード */
#include "CGameObject.h"
#include "CCamera.h"

/* 名前空間 */
using namespace DirectX;

//コンストラクタ
CGameObject::CGameObject(ID3D11Buffer* _vb, ID3D11ShaderResourceView* _tex, FLOAT_XY _uv)
{
	//使用カメラの初期化
	useCamera = nullptr;

	//モデルの作成
	D3D_CreateSquare({ 0.0f ,0.0f }, { 1.0f ,1.0f }, _uv, &_vb);

	//uv分割の設定
	sprit = _uv;

	//引数で受け取った頂点バッファとテクスチャをセットする
	vertexBuffer = _vb;
	texture = _tex;
}

//デストラクタ
CGameObject::~CGameObject()
{
	SAFE_RELEASE(vertexBuffer);
}

//Update
void CGameObject::Update()
{
	//全てのオブジェクト共通のUpdate処理

	//オブジェクトの位置とコライダーの中心を合わせる
	this->Bcol.centerX = this->transform.position.x;
	this->Bcol.centerY = this->transform.position.y;

	//ここにUpdate処理を記述する
	//共通処理以外は継承先にoverrideして記述すること
}

//Draw
void CGameObject::Draw()
{
	//コンストバッファの作成
	ConstBuffer cb;

	//平行投影の行列作成
	//第１,第２引数：映し出す横縦の長さ
	//第３,第４引数：映し出す空間の奥行(手前と最奥)
	float scaleScreen = 1.0f;		//ワールドのスケール
	cb.matrixProj = XMMatrixOrthographicLH(4.0f * scaleScreen, 2.25f * scaleScreen, 0.0f, 3.0f);

	//カメラが設定されているならカメラの行列もかけ合わせる
	cb.matrixProj = useCamera != nullptr ?
		XMMatrixTranspose(useCamera->GetMatrixView() * cb.matrixProj) : XMMatrixTranspose(cb.matrixProj);

	//移動行列
	XMMATRIX matrixMove = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
	//拡大縮小行列
	XMMATRIX matrixScale = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	//回転行列
	XMMATRIX matrixRotation = XMMatrixRotationZ(XMConvertToRadians(transform.rotation));
	//行列は掛け算で合成できる ※掛ける順番が影響する 今回は拡大、縮小してから移動移動させる
	cb.matrixWorld = matrixScale * matrixRotation * matrixMove;
	cb.matrixWorld = XMMatrixTranspose(cb.matrixWorld);

	//UVアニメーションの行列を作成
	// XMMatrixTranslation＝移動行列を作る関数
	cb.matrixTex = XMMatrixTranslation(uv.x, uv.y, 0.0f);
	// XMMatrixTranspose＝転置行列を作る
	cb.matrixTex = XMMatrixTranspose(cb.matrixTex);

	//マテリアル色をシェーダーにセット
	cb.materialDiffuse = materialDiffuse;

	//行列をシェーダーに渡す
	m_pImmediateContext->UpdateSubresource(m_pConstBuffer, 0, NULL, &cb, 0, 0);

	//今からDrawする頂点バッファ(モデル)を指定する
	m_pImmediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offsets);
	//ピクセルシェーダーにテクスチャを渡す
	m_pImmediateContext->PSSetShaderResources(0, 1, &texture);
	//描画命令
	//第一引数は描画する頂点の数
	m_pImmediateContext->Draw(6, 0);
}

//使用するカメラを設定をする
void CGameObject::SetUseingCamera(CCamera* setCamera)
{
	//カメラのポインタを受け取る
	useCamera = setCamera;
}

void CGameObject::TextureCutout(int u_num, int v_num)
{
	//指定された分だけテクスチャを移動させる
	uv.x = sprit.x * u_num;
	uv.y = sprit.y * v_num;
}

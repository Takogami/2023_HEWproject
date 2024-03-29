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
CGameObject::CGameObject(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type)
{
	//アニメーションクラスの実体化
	anim = new CAnimation;
	//使用カメラの初期化
	useCamera = nullptr;

	//モデルの作成
	D3D_CreateSquare({ 0.0f ,0.0f }, { 1.0f ,1.0f }, uv, &vb);

	//uv分割の設定
	sprit = uv;

	//引数で受け取った頂点バッファとテクスチャをセットする
	vertexBuffer = vb;
	texture = tex;
	objectType = type;
}

//デストラクタ
CGameObject::~CGameObject()
{
	// animの二重deleteを防ぐ
	if (anim != nullptr)
	{
		delete anim;
		anim = nullptr;
	}
	SAFE_RELEASE(vertexBuffer);
}

//Update
void CGameObject::Update()
{
	//全てのオブジェクト共通のUpdate処理

	// オブジェクトがアクティブでないなら更新は行わない
	if (!active)
	{
		return;
	}

	//オブジェクトの位置とコライダーの中心を合わせる
	this->Bcol.centerX = this->transform.position.x;
	this->Bcol.centerY = this->transform.position.y;

	// アニメーションの更新
	anim->Update();
	// uv移動量を取得
	if (anim_switch)
	{
		// アニメーションを行うオブジェクトなら、animから移動量を獲得
		uv = anim->GetUV();
	}

	//ここにUpdate処理を記述する
	//共通処理以外は継承先にoverrideして記述すること
}

//Draw
void CGameObject::Draw()
{
	// オブジェクトがアクティブでないなら描画は行わない
	if (!active)
	{
		return;
	}

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

void CGameObject::InitAnimParameter(bool iniPlaying, int spritU, int spritV, ANIM_PATTERN pattern, float sp)
{
	anim_switch = true;
	// 初期状態で再生するか設定
	if (iniPlaying)
	{
		anim->PlayAnimation();
	}
	else
	{
		anim->StopAnimation();
	}
	// アニメーションクラスのカウンタを初期化する
	anim->ResetAnimation();
	// 横方向の分割数を設定
	anim->SetSpritU(spritU);
	// 縦方向の分割数を設定
	anim->SetSpritV(spritV);
	// uv移動量の設定
	anim->SetMovementUV(sprit);
	// 初期に再生するパターンを設定
	anim->SetAnimationPattern(pattern);
	// 初期に再生するパターンを設定
	anim->SetAnimationSpeed(sp);
}

void CGameObject::SetAnimationSpeed(float sp)
{
	// アニメーションクラスに速度を送る
	anim->SetAnimationSpeed(sp);
}

void CGameObject::SetAnimationPattern(ANIM_PATTERN pattern)
{
	// アニメーションクラスにパターンを送る
	anim->SetAnimationPattern(pattern);
}

void CGameObject::PlayAnimation()
{
	// アニメーションクラスに再生命令を送る
	anim->PlayAnimation();
}

void CGameObject::StopAnimation()
{
	// アニメーションクラスに停止命令を送る
	anim->StopAnimation();
}

void CGameObject::ResetAnimation()
{
	// アニメーションクラスにリセット命令を送る
	anim->ResetAnimation();
}

void CGameObject::TextureCutout(int u_num, int v_num)
{
	//指定された分だけテクスチャを移動させる
	uv.x = sprit.x * u_num;
	uv.y = sprit.y * v_num;
}

void CGameObject::SetObjectType(OBJECT_TYPE _objectType)
{
	this->objectType = _objectType;
}

OBJECT_TYPE CGameObject::GetObjectType() const
{
	return objectType;
}
//--------------------------------------------------------------------------
// CCamera.cpp
// 
// 作成者:辻 幸宏
// 
// 概要:カメラを作成できるクラス
//      このファイルではメソッドの本体を記述している
//      Updateメソッドで常に行列を作成し、GetMatrixViewメソッドで行列を渡す
//      SetCameraPositionメソッドで位置を指定することが可能
// 
// 最終更新日時:2023/10/27
//--------------------------------------------------------------------------


//	ここに追加

/* インクルード */
#include "CCamera.h"

// コンストラクタ
CCamera::CCamera()
{
	// 単位行列の初期化
	matrixView = DirectX::XMMatrixIdentity();

	// XMVECTOR型変数の初期化
	eye = DirectX::XMVectorZero();
	focus = DirectX::XMVectorZero();
	up = DirectX::XMVectorZero();

	//カメラ位置の初期化
	cameraPos = { 0, 0 };
}

// デストラクタ
CCamera::~CCamera()
{
}

// カメラ位置を設定
void CCamera::SetCameraPosition(float pos_x, float pos_y)
{
	//カメラポジションのセット
	cameraPos = { pos_x, pos_y };
}

// View変換行列の更新
void CCamera::Update()
{
	//View変換行列の作成 ＝ カメラ用の行列
	eye = DirectX::XMVectorSet(cameraPos.x, cameraPos.y, -1, 0);	//視点の位置
	focus = DirectX::XMVectorSet(cameraPos.x, cameraPos.y, 1, 0);	//見ている位置
	up = DirectX::XMVectorSet(0, 1, 0, 0);							//カメラの上方向

	matrixView = DirectX::XMMatrixLookAtLH(eye, focus, up);
}

// View変換行列の取得
DirectX::XMMATRIX CCamera::GetMatrixView()
{
	return matrixView;
}


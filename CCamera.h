//--------------------------------------------------------------------------
// CCamera.h
// 
// 作成者:辻 幸宏
// 
// 概要:カメラを作成できるクラス
//      Updateメソッドで常に行列を作成し、GetMatrixViewメソッドで行列を渡す
//      SetCameraPositionメソッドで位置を指定することが可能
// 
// 最終更新日時:2023/10/27
//--------------------------------------------------------------------------

#pragma once

/* インクルード */
#include "direct3d.h"

//CCameraクラス
class CCamera
{
private:
	/* メンバ変数 */

	DirectX::XMVECTOR eye;		// 目の位置
	DirectX::XMVECTOR focus;	// どこを見ているか
	DirectX::XMVECTOR up;		// カメラの上方向

	// View変換行列
	DirectX::XMMATRIX matrixView;

public:
	/* メンバ変数 */

	//カメラ位置
	DirectX::XMFLOAT2 cameraPos;

	/* メソッド */

	// コンストラクタ
	CCamera();
	// デストラクタ
	~CCamera();
	// View変換行列の取得
	DirectX::XMMATRIX GetMatrixView();

	// View変換行列の更新
	void Update();
};


#pragma once			//重複インクルードを自動防止する

#include <d3d11.h>		//DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>//DirectXの数学関連のヘッダーファイル
#include "DirectWhite.h"

//DirectXの解放の簡略化マクロ
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

//構造体の定義
//xyを表す構造体
struct FLOAT_XY
{
	float x, y;
};

//定数バッファ用構造体
struct ConstBuffer
{
	//UV座標移動行列
	DirectX::XMMATRIX matrixTex;
	//投影行列
	DirectX::XMMATRIX matrixProj;
	//ワールド変換行列
	DirectX::XMMATRIX matrixWorld;
	//モデルに適用するマテリアル色
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };
};

//プロトタイプ宣言
HRESULT D3D_Create(HWND hwnd);
void    D3D_Release();

//四角形ポリゴンを作成し、頂点バッファ生成を行う
//※第4引数:ポインタ型変数のアドレスが入るので*が二つ付く
void D3D_CreateSquare(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vd);

//テクスチャを読み込む
//引数:(1)ファイル名 (2)テクスチャ格納用変数のアドレス
HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture);

//画面塗りつぶしと設定を行う関数
void D3D_ClearScreen();

//画面更新する関数
void D3D_UpdateScreen();

//グローバル変数のextern宣言
//※あくまで名簿を外部に公開しているだけなので新しい変数を作っているわけではない

extern ID3D11DeviceContext* m_pImmediateContext;   //コンテキスト = 描画関連を司る機能
extern const UINT strides;
extern const UINT offsets;

extern ID3D11BlendState* m_pBlendStateAlpha;       //ブレンドステート用変数（アルファブレンディング）
extern ID3D11BlendState* m_pBlendStateAdditive;    //ブレンドステート用変数（加算合成）

// 定数バッファ用変数を他cppに公開
extern ID3D11Buffer* m_pConstBuffer;
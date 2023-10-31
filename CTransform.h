//--------------------------------------------------------------------------
// CTranceform.h
// 
// 作成者:辻 幸宏
// 概要:ゲームオブジェクトの位置、大きさ(スケール)、回転率を保持するクラス
// 
// 最終更新日時:2023/10/12
//--------------------------------------------------------------------------

#pragma once

//FLOAT3構造体
//float型の値を３つ格納
typedef struct
{
	float x;	//x値
	float y;	//y値
	float z;	//z値
}VECTOR3;

//CTranceformクラス
class CTransform
{

public:

	/* メンバ変数 */

	VECTOR3 position;	//位置座標
	VECTOR3 scale;		//スケール
	float rotation;		//回転率

	/* メソッド */
	
	CTransform();			//コンストラクタ 各数値の初期化を行う
	~CTransform();			//デストラクタ

	// *演算子のオーバーロード
	// 比率を維持して拡大、縮小を実現　※2Dのみ対応
	inline void operator *(float n)
	{
		this->scale.x *= n;
		this->scale.y *= n;
	}
};
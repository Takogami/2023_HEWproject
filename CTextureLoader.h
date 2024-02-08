//-------------------------------------------------------------------------------
// CTextureLoader.h
// 
// 作成者:辻 幸宏
// 
// 概要:テクスチャをロードし、それを返すクラス
//      シングルトンで実装しているため、唯一のインスタンスを取得する必要がある
//      パスと識別子を追加するだけでテクスチャのロードを行える
// 
//      10/30:enumクラスを外に移動
//            GetTexのID指定が簡単に
// 
// 最終更新日時:2023/10/30
//-------------------------------------------------------------------------------

#pragma once

/* インクルード */
#include "direct3d.h"
#include <list>

// テクスチャ情報格納用構造体
// パスとテクスチャを読み込む変数のポインタ
typedef struct
{
	const wchar_t* path;
	ID3D11ShaderResourceView* tex;
}TEX_INFO;

enum class TEX_ID	// テクスチャ識別子列挙型
{
	TAKO,
	STAGE,
	NUM,
	WINDRIGHT_POS,	//	風の起こる位置（右向き）
	TITLE,
	TILE,
	BG,
	PLAYER,
	BOOK,
	STRING_BG,
	GAMEOVER,
	GAMEOVER_STRING,
	SELECT_FLAME,
	CURSOR,
};

// CTextureLoaderクラス
class CTextureLoader
{
private:
	/* メンバ変数 */
 
	static CTextureLoader* instance;		// 唯一のインスタンスを格納するためのポインタ

	std::list<TEX_INFO> texList;			// テクスチャ情報のリスト
	std::list<const wchar_t*> pathList =	// パスのリスト
	{
		L"asset/Tako.jpg",
		L"asset/Madoka_Magika_(Logo).png",
		L"asset/suuji.png",
		L"asset/Fade.png",	//	試しでテクスチャ読み込み(風の右向き)
		L"asset/title.png",
		L"asset/tile.png",
		L"asset/bg.png",
		L"asset/Playeranim5.png",
		L"asset/book.png",
		L"asset/stringBg.png",
		L"asset/GameOver.png",
		L"asset/GameOverString.png",
		L"asset/selectFlame.png",
		L"asset/cursor.png",
		L"asset/heart.png",
		L"asset/heart_half.png",
		L"asset/heart_half2.png",
		L"asset/heart_enpty.png",
		L"asset/timer.png",
		L"asset/scoreBoard.png",
	};

	/* メソッド */

	CTextureLoader();				//コンストラクタ
	~CTextureLoader();				//デストラクタ

	static void CleanupSingleton();	//アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)

public:
	/* メソッド */

	void LoadTexture();							// テクスチャをロードする
	void UnloadTexture();						// テクスチャをアンロードする

	ID3D11ShaderResourceView* GetTex(TEX_ID id);// テクスチャを取得する

	static CTextureLoader* GetInstance();		//インスタンスを取得するためのメソッド
};


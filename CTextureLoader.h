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
	BLOCK,
	NUM,
	FADE,
	TITLE,
	TILE,
	BG,
	PLAYER,
	BOOK,
	STRING_BG,
	GAMEOVER,
	GAMEOVER_STRING,
	SELECT_FLAME,
	S1_SELECT_FLAME,
	CURSOR,
	HEART,
	HALF_HEART_L,
	HALF_HEART_R,
	TIMER,
	SCORE_BOARD,
	ENEMY,
	BOARD,
	PLAY,
	EXIT,
	RULER,
	BOOK_OBJ1,
	BOOK_OBJ2,
	RETRY,
	STAGE_SELECT,
	GOTO_TITLE,
	CLEAR,
	CLEAR_STRING,
	WIND,
	FADE_ANIM,
	DAMAGE_FX,
	ERASER,
	WIND_UP,
	WIND_LEFT,
	WIND_RIGHT,
	BG2,
	darkTile,
	DTILEX,
	PENCIL,
	Senpuuki,
	NOMAL_TILE,
	DTILE_DOWN,
	TITLE_BG,
	HATA,
	KANBAN,
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
		L"asset/block.png",
		L"asset/suuji.png",
		L"asset/Fade.png",	//	試しでテクスチャ読み込み(風の右向き)
		L"asset/title.png",
		L"asset/gabyouue.png",
		L"asset/bg.png",
		L"asset/Playeranim.png",
		L"asset/book.png",
		L"asset/stringBg.png",
		L"asset/GameOver.png",
		L"asset/GameOverString.png",
		L"asset/selectFlame.png",
		L"asset/s1_selectFlame.png",
		L"asset/cursor.png",
		L"asset/heart.png",
		L"asset/heart_half.png",
		L"asset/heart_half_right.png",
		L"asset/timer.png",
		L"asset/scoreBoard.png",
		L"asset/enemy.png",
		L"asset/waku.png",
		L"asset/play.png",
		L"asset/exit.png",
		L"asset/ruler.png",
		L"asset/bookObj1.png",
		L"asset/bookObj2.png",
		L"asset/retry.png",
		L"asset/selectStage.png",
		L"asset/goToTitle.png",
		L"asset/clear.png",
		L"asset/clearString.png",
		L"asset/Senpuuki.png",
		L"asset/fadeAnim.png",
		L"asset/damageFX.png",
		L"asset/kesigomu.png",
		L"asset/wind_up.png",
		L"asset/wind_left.png",
		L"asset/wind_right.png",
		L"asset/bg2.png",
		L"asset/Dtile.png",
		L"asset/gabyou3.png",
		L"asset/pencil.png",
		L"asset/Senpuuki.png",
		L"asset/nomal.png",
		L"asset/gabyousita.png",
		L"asset/titleBg.png",
		L"asset/hata.png",
		L"asset/kanban.png",
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


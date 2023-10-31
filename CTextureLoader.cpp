//-------------------------------------------------------------------------------
// CTextureLoader.cpp
// 
// 作成者:辻 幸宏
// 
// 概要:テクスチャをロードし、それを返すクラス
//      このファイルではメソッドの本体を記述している
//      シングルトンで実装しているため、唯一のインスタンスを取得する必要がある
//      パスと識別子を追加するだけでテクスチャのロードを行える
// 
//      10/30:enumクラスを外に移動
//            GetTexのID指定が簡単に
// 
// 最終更新日時:2023/10/30
//-------------------------------------------------------------------------------

/* インクルード */
#include "CTextureLoader.h"

// CTextureLoaderクラスのstaticメンバ変数の初期化
CTextureLoader* CTextureLoader::instance = nullptr;

//コンストラクタ
CTextureLoader::CTextureLoader()
{
	//パスのリストの内容を全てtexListにpushする
	for (std::list<const wchar_t*>::iterator it = pathList.begin(); it != pathList.end(); ++it)
	{
		//pathをリストに追加
		texList.push_back({ *it, nullptr});
	}
}

//デストラクタ
CTextureLoader::~CTextureLoader()
{
}

//全てのテクスチャをロードする
void CTextureLoader::LoadTexture()
{
	//texListに格納されたパスの数だけテクスチャを読み込む
	for (std::list<TEX_INFO>::iterator it = texList.begin(); it != texList.end(); ++it)
	{
		//テクスチャ読み込み
		D3D_LoadTexture(it->path, &it->tex);
	}
}

//全てのテクスチャをアンロードする
void CTextureLoader::UnloadTexture()
{
	//texList内のポインタ変数を解放する
	for (std::list<TEX_INFO>::iterator it = texList.begin(); it != texList.end(); ++it)
	{
		//メモリを解放
		SAFE_RELEASE(it->tex);
	}
}

//テクスチャの取得を行う関数
//引数は クラス名::TEX_ID::任意のID で指定すること
ID3D11ShaderResourceView* CTextureLoader::GetTex(TEX_ID id)
{
	//イテレータの初期化
	std::list<TEX_INFO>::iterator it = texList.begin();
	//渡されたidのテクスチャを参照する
	std::advance(it, (int)id);

	//イテレータ内の要素を参照し、その内のtexを返す
	return it->tex;
}

//唯一のインスタンスを返す関数
CTextureLoader* CTextureLoader::GetInstance()
{
	// シングルトンが存在していないなら生成する
	if (!instance)
	{
		// シングルトンの生成
		instance = new CTextureLoader();
		//コールバックとして登録
		std::atexit(CleanupSingleton);
	}
	//唯一のインスタンスを返す
	return instance;
}

//シングルトンの解放処理
void CTextureLoader::CleanupSingleton()
{
	//インスタンスがあるなら解放する
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

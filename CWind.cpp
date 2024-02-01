#include "CWind.h"

//明示的に親クラスのコンストラクタを呼び出す
CWind::CWind(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
}

CWind::~CWind()
{
	// 親クラスのコンストラクタを明示的に呼び出す
	// 頂点バッファの解放を行う
	CGameObject::~CGameObject();
}

void CWind::Update()
{
	// 親クラスの更新を明示的に呼び出す
	CGameObject::Update();
}

void CWind::SetWindStrangth(float power)
{
	// 変更前の座標を保存
	windStrength = power;
}

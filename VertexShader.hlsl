/* 頂点シェーダー */

//頂点のデータを表す構造体(受け取り用)
struct VS_IN
{
    float4 pos : POSITION0; //位置座標が入る
    float2 tex : TEX;       //UV座標が入る
};

//頂点のデータを表す構造体(送信用)
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

//グローバル変数の宣言
//定数バッファ受け取り用
cbuffer ConstBuffer : register(b0)
{
    //UV座標移動行列
    matrix matrixTex;
    //投影行列
    matrix matrixProj;
    //ワールド変換行列
    matrix matrixWorld;
    //マテリアル色
    float4 materialDiffuse;
}

//頂点シェーダーのエントリポイント
VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;

    //ワールド変換行列を頂点に掛ける
    input.pos = mul(input.pos,matrixWorld);

    //平行投影のため行列を頂点に掛ける
    output.pos = mul(input.pos,matrixProj);

    //UV座標を移動させる
    float4 uv;
    uv.xy = input.tex;  //行列掛け算のため、float4型に移す
    uv.z = 0.0f;
    uv.w = 1.0f;

    //UV座標と移動行列を掛け算
    uv = mul(uv, matrixTex);

    //掛け算の結果を送信用変数にセットする
    output.tex = uv.xy;

    return output;
}
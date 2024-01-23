#include <atltypes.h>	//CRectを使うためのヘッダーファイル
#include "direct3d.h"
#include "WICTextureLoader.h"   //テクスチャ読み込み用ライブラリ

//コンパイル済みシェーダーをインクルード
#include "VertexShader.h"
#include "PixelShader.h"

//ライブラリのリンク設定
#pragma comment (lib,"d3d11.lib")

//構造体定義
//頂点データを表す構造体
struct Vertex {

    //頂点の位置座標
    float x, y, z;
    //UV座標(テクスチャ座標)
    float u, v;

};

//グローバル変数の宣言
//ID3D11で始まるポインタ型変数は解放する必要がある
ID3D11Device* m_pDevice;                    //デバイス = DirectXの各種機能を作る
ID3D11DeviceContext* m_pImmediateContext;   //コンテキスト = 描画関連を司る機能
IDXGISwapChain* m_pSwapChain;               //スワップチェイン = ダブルバッファ
ID3D11RenderTargetView* m_pRenderTargetView;//レンダーターゲットビュー = 描画先を表す機能
ID3D11Texture2D* m_pDepthStencilTexture;    //深度バッファ用テクスチャ
ID3D11DepthStencilView* m_pDepthStencilView;//深度バッファ
ID3D11InputLayout* m_pInputLayout;          //インプットレイアウト
ID3D11VertexShader* m_pVertexShader;        //頂点シェーダーオブジェクト
ID3D11PixelShader* m_pPixelShader;          //ピクセルシェーダーオブジェクト
ID3D11SamplerState* m_pSampler;             //サンプラー
ID3D11Buffer* m_pConstBuffer;               //定数バッファ用
D3D11_VIEWPORT          m_Viewport;         //ビューポート
ID3D11BlendState* m_pBlendStateAlpha;       //ブレンドステート用変数（アルファブレンディング）
ID3D11BlendState* m_pBlendStateAdditive;    //ブレンドステート用変数（加算合成）
DirectWrite* directWrite;
FontData fontData;

//IASetVertexBufferで使用する変数
const UINT strides = sizeof(Vertex);
const UINT offsets = 0;

//Direct3Dの初期化をする
HRESULT D3D_Create(HWND hwnd)
{
    //HRESULT型　WINDOWSプログラムで関数実行の成功・失敗を受け取る
    HRESULT  hr;

    UINT flags = 0;
    flags |= D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL level;

    CRect                rect;
    DXGI_SWAP_CHAIN_DESC scDesc;

    ::GetClientRect(hwnd, &rect);
    ::ZeroMemory(&scDesc, sizeof(scDesc));
    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Width = rect.Width();
    scDesc.BufferDesc.Height = rect.Height();
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = hwnd;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.Windowed = TRUE;

    //デバイスとスワップチェインを同時に作成する関数の呼び出し
    hr = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        pLevels,
        1,
        D3D11_SDK_VERSION,
        &scDesc,
        &m_pSwapChain,
        &m_pDevice,
        &level,
        &m_pImmediateContext);
    if (FAILED(hr)) //上の関数呼び出しが失敗していないかをifでチェック
        return hr;

    ID3D11Texture2D* pBackBuffer;

    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
        return hr;

    //レンダーターゲットを作成する関数を呼び出す
    hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    //深度ステンシルバッファ(Zバッファ)の作成
    //※深度バッファ(Zバッファ) → 奥行を判定して前後関係を正しく描画できる
    D3D11_TEXTURE2D_DESC txDesc;
    ZeroMemory(&txDesc, sizeof(txDesc));
    txDesc.Width = rect.Width();
    txDesc.Height = rect.Height();
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    txDesc.SampleDesc.Count = 1;
    txDesc.SampleDesc.Quality = 0;
    txDesc.Usage = D3D11_USAGE_DEFAULT;
    txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    txDesc.CPUAccessFlags = 0;
    txDesc.MiscFlags = 0;
    hr = m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);
    if (FAILED(hr))
        return hr;

    D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.Format = txDesc.Format;
    dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsDesc.Texture2D.MipSlice = 0;
    hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
    if (FAILED(hr))
        return hr;

    //インプットレイアウト作成
    //頂点１つあたりにどんなデータが含まれるかをDirect3Dに伝える
    D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{

    //位置座標があるということを伝える
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,
    D3D11_INPUT_PER_VERTEX_DATA, 0 },
    //UV座標があるということを伝える
    { "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, 
    D3D11_INPUT_PER_VERTEX_DATA, 0 },

    };

    hr = m_pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
        g_vs_main, sizeof(g_vs_main),
        &m_pInputLayout);
    if (FAILED(hr))
        return hr;

    //シェーダーオブジェクトの作成
    //コンパイル済みシェーダーをVRAMに配置してGPUが実行できるようにする
    hr = m_pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
    if (FAILED(hr))
        return hr;

    hr = m_pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
    if (FAILED(hr))
        return hr;

    //ビューポートを作成
    //画面分割などに使う、描画領域の指定のこと
    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;
    m_Viewport.Width = (FLOAT)rect.Width();
    m_Viewport.Height = (FLOAT)rect.Height();
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;

    //サンプラーの作成
    //→テクスチャ拡大縮小時のアルゴリズム(拡大縮小される時の補間方法などを指定)
    D3D11_SAMPLER_DESC smpDesc;

    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));

    //適応されるフィルター(アルゴリズム)の種類
    //LINEAR : なめらかに POINT : くっきりと
    smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
    if (FAILED(hr))
        return hr;

    //定数バッファ作成
    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(ConstBuffer);
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    hr = m_pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstBuffer);
    if (FAILED(hr))
        return hr;

    // ブレンドステート作成
    // →透過処理や加算合成を可能にする色の合成方法
    // 加算合成：エフェクトなどに使用する色が明るくなる合成方法
    D3D11_BLEND_DESC BlendState;
    ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
    BlendState.AlphaToCoverageEnable = FALSE;
    BlendState.IndependentBlendEnable = FALSE;
    BlendState.RenderTarget[0].BlendEnable = TRUE;
    BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    // DestBlead：背景色に掛け合わせる係数
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    //アルファブレンドの設定を作る
    BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAlpha);

    m_pImmediateContext->OMSetBlendState(m_pBlendStateAlpha, NULL, 0xffffffff);

    //加算合成の設定を作る
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAdditive);

    directWrite = new DirectWrite(&fontData);
    directWrite->Init(m_pSwapChain);
    directWrite->SetFont(fontData);

    return hr;
}

//Direct3Dの解放をする(終了する)
//※DirectXの各機能は作成した後、アプリの終了後に必ず解放しなければならない
void D3D_Release()
{
    if (m_pImmediateContext) {
        m_pImmediateContext->ClearState();
    }

    SAFE_RELEASE(m_pRenderTargetView);
    SAFE_RELEASE(m_pSwapChain);
    SAFE_RELEASE(m_pImmediateContext);
    SAFE_RELEASE(m_pDevice);
    SAFE_RELEASE(m_pDepthStencilTexture);
    SAFE_RELEASE(m_pDepthStencilView);

    SAFE_RELEASE(m_pInputLayout);
    SAFE_RELEASE(m_pVertexShader);
    SAFE_RELEASE(m_pPixelShader);

    SAFE_RELEASE(m_pSampler);

    //定数バッファ解放
    SAFE_RELEASE(m_pConstBuffer);

    //アルファブレンドステート解放
    SAFE_RELEASE(m_pBlendStateAlpha);
    //加算合成ブレンドステート解放
    SAFE_RELEASE(m_pBlendStateAdditive);

    // directWhiteを解放
    if (directWrite)
    {
        delete directWrite;
        directWrite = nullptr;
    }
}

void D3D_CreateSquare(FLOAT_XY center, FLOAT_XY size, FLOAT_XY uv ,ID3D11Buffer** vb)
{
    float l = center.x - size.x / 2.0f;
    float r = l + size.x;
    float t = center.y + size.y / 2.0f;
    float b = t - size.y;

    //頂点データを決める
    //(参考)画面座標
    //左右 = X座標 (右が+方向)　上下 = Y座標 (上が+方向)
    //画面中心が = XY原点(0.0f,0.0f)
    //画面端 = 左X = 1.0f 右 = -1.0f 上Y = 1.0f 下Y = -1.0f
    Vertex vertexList[] = {

        //頂点が時計回りに三角形を形成する側がポリゴンの表になる
        //裏になってしまうと描画されない
        { l, t, 0.5f, 0.0f, 0.0f},      //0番目の頂点座標 {x, y, z, u, v}
        { r, b, 0.5f ,uv.x, uv.y},      //1番目の頂点座標
        { l, b, 0.5f ,0.0f ,uv.y},      //2番目の頂点座標

        { l, t, 0.5f, 0.0f, 0.0f},    //3番目の頂点座標
        { r, t, 0.5f, uv.x, 0.0f},    //4番目の頂点座標
        { r, b, 0.5f ,uv.x ,uv.y},    //5番目の頂点座標

    };

    //頂点バッファを作成する
    //※頂点バッファ : VRAMに頂点データを置くための機能
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = sizeof(vertexList);      //確保するバッファサイズを指定
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //頂点バッファサイズを指定
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResourceData;
    subResourceData.pSysMem = vertexList;            //VRAMに送るデータを指定
    subResourceData.SysMemPitch = 0;
    subResourceData.SysMemSlicePitch = 0;

    //頂点バッファ作成して、それを変数(第３引数)に保存
    m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, vb);
}

HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture)
{
    //第4引数:読み込んだテクスチャを保持する変数
    HRESULT hr = DirectX::CreateWICTextureFromFile(m_pDevice, filename, NULL, texture);

    //読み込みに失敗した場合
    if (FAILED(hr))
        MessageBoxA(NULL, "テクスチャ読み込みに失敗", "エラー", MB_OK | MB_ICONERROR);

    return hr;
}

void D3D_ClearScreen()
{
    //画面塗りつぶし色
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

    //描画先のキャンバスと使用する深度バッファを指定するを指定する
    //深度バッファを使わないときは第３引数をNULLに指定する
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
    //描画先キャンバスを塗りつぶす
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    //深度バッファをリセットする
    m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_pImmediateContext->IASetInputLayout(m_pInputLayout);
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
    m_pImmediateContext->RSSetViewports(1, &m_Viewport);
    m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

    //ピクセルシェーダーにサンプラーを渡す
    m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);

    //定数バッファに頂点シェーダーをセットする
    m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstBuffer);
    //定数バッファにピクセルシェーダーをセットする
    m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstBuffer);
}

void D3D_UpdateScreen()
{
    //ダブルバッファの切り替えを行い画面を更新する
    m_pSwapChain->Present(0, 0);
}


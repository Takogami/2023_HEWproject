#include <atltypes.h>	//CRect���g�����߂̃w�b�_�[�t�@�C��
#include "direct3d.h"
#include "WICTextureLoader.h"   //�e�N�X�`���ǂݍ��ݗp���C�u����

//�R���p�C���ς݃V�F�[�_�[���C���N���[�h
#include "VertexShader.h"
#include "PixelShader.h"

//���C�u�����̃����N�ݒ�
#pragma comment (lib,"d3d11.lib")

//�\���̒�`
//���_�f�[�^��\���\����
struct Vertex {

    //���_�̈ʒu���W
    float x, y, z;
    //UV���W(�e�N�X�`�����W)
    float u, v;

};

//�O���[�o���ϐ��̐錾
//ID3D11�Ŏn�܂�|�C���^�^�ϐ��͉������K�v������
ID3D11Device* m_pDevice;                    //�f�o�C�X = DirectX�̊e��@�\�����
ID3D11DeviceContext* m_pImmediateContext;   //�R���e�L�X�g = �`��֘A���i��@�\
IDXGISwapChain* m_pSwapChain;               //�X���b�v�`�F�C�� = �_�u���o�b�t�@
ID3D11RenderTargetView* m_pRenderTargetView;//�����_�[�^�[�Q�b�g�r���[ = �`����\���@�\
ID3D11Texture2D* m_pDepthStencilTexture;    //�[�x�o�b�t�@�p�e�N�X�`��
ID3D11DepthStencilView* m_pDepthStencilView;//�[�x�o�b�t�@
ID3D11InputLayout* m_pInputLayout;          //�C���v�b�g���C�A�E�g
ID3D11VertexShader* m_pVertexShader;        //���_�V�F�[�_�[�I�u�W�F�N�g
ID3D11PixelShader* m_pPixelShader;          //�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
ID3D11SamplerState* m_pSampler;             //�T���v���[
ID3D11Buffer* m_pConstBuffer;               //�萔�o�b�t�@�p
D3D11_VIEWPORT          m_Viewport;         //�r���[�|�[�g
ID3D11BlendState* m_pBlendStateAlpha;       //�u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�j
ID3D11BlendState* m_pBlendStateAdditive;    //�u�����h�X�e�[�g�p�ϐ��i���Z�����j
DirectWrite* directWrite;
FontData fontData;

//IASetVertexBuffer�Ŏg�p����ϐ�
const UINT strides = sizeof(Vertex);
const UINT offsets = 0;

//Direct3D�̏�����������
HRESULT D3D_Create(HWND hwnd)
{
    //HRESULT�^�@WINDOWS�v���O�����Ŋ֐����s�̐����E���s���󂯎��
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

    //�f�o�C�X�ƃX���b�v�`�F�C���𓯎��ɍ쐬����֐��̌Ăяo��
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
    if (FAILED(hr)) //��̊֐��Ăяo�������s���Ă��Ȃ�����if�Ń`�F�b�N
        return hr;

    ID3D11Texture2D* pBackBuffer;

    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
        return hr;

    //�����_�[�^�[�Q�b�g���쐬����֐����Ăяo��
    hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    //�[�x�X�e���V���o�b�t�@(Z�o�b�t�@)�̍쐬
    //���[�x�o�b�t�@(Z�o�b�t�@) �� ���s�𔻒肵�đO��֌W�𐳂����`��ł���
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

    //�C���v�b�g���C�A�E�g�쐬
    //���_�P������ɂǂ�ȃf�[�^���܂܂�邩��Direct3D�ɓ`����
    D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{

    //�ʒu���W������Ƃ������Ƃ�`����
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,
    D3D11_INPUT_PER_VERTEX_DATA, 0 },
    //UV���W������Ƃ������Ƃ�`����
    { "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, 
    D3D11_INPUT_PER_VERTEX_DATA, 0 },

    };

    hr = m_pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
        g_vs_main, sizeof(g_vs_main),
        &m_pInputLayout);
    if (FAILED(hr))
        return hr;

    //�V�F�[�_�[�I�u�W�F�N�g�̍쐬
    //�R���p�C���ς݃V�F�[�_�[��VRAM�ɔz�u����GPU�����s�ł���悤�ɂ���
    hr = m_pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
    if (FAILED(hr))
        return hr;

    hr = m_pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
    if (FAILED(hr))
        return hr;

    //�r���[�|�[�g���쐬
    //��ʕ����ȂǂɎg���A�`��̈�̎w��̂���
    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;
    m_Viewport.Width = (FLOAT)rect.Width();
    m_Viewport.Height = (FLOAT)rect.Height();
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;

    //�T���v���[�̍쐬
    //���e�N�X�`���g��k�����̃A���S���Y��(�g��k������鎞�̕�ԕ��@�Ȃǂ��w��)
    D3D11_SAMPLER_DESC smpDesc;

    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));

    //�K�������t�B���^�[(�A���S���Y��)�̎��
    //LINEAR : �Ȃ߂炩�� POINT : ���������
    smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
    if (FAILED(hr))
        return hr;

    //�萔�o�b�t�@�쐬
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

    // �u�����h�X�e�[�g�쐬
    // �����ߏ�������Z�������\�ɂ���F�̍������@
    // ���Z�����F�G�t�F�N�g�ȂǂɎg�p����F�����邭�Ȃ鍇�����@
    D3D11_BLEND_DESC BlendState;
    ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
    BlendState.AlphaToCoverageEnable = FALSE;
    BlendState.IndependentBlendEnable = FALSE;
    BlendState.RenderTarget[0].BlendEnable = TRUE;
    BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    // DestBlead�F�w�i�F�Ɋ|�����킹��W��
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    //�A���t�@�u�����h�̐ݒ�����
    BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAlpha);

    m_pImmediateContext->OMSetBlendState(m_pBlendStateAlpha, NULL, 0xffffffff);

    //���Z�����̐ݒ�����
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAdditive);

    directWrite = new DirectWrite(&fontData);
    directWrite->Init(m_pSwapChain);
    directWrite->SetFont(fontData);

    return hr;
}

//Direct3D�̉��������(�I������)
//��DirectX�̊e�@�\�͍쐬������A�A�v���̏I����ɕK��������Ȃ���΂Ȃ�Ȃ�
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

    //�萔�o�b�t�@���
    SAFE_RELEASE(m_pConstBuffer);

    //�A���t�@�u�����h�X�e�[�g���
    SAFE_RELEASE(m_pBlendStateAlpha);
    //���Z�����u�����h�X�e�[�g���
    SAFE_RELEASE(m_pBlendStateAdditive);

    // directWhite�����
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

    //���_�f�[�^�����߂�
    //(�Q�l)��ʍ��W
    //���E = X���W (�E��+����)�@�㉺ = Y���W (�オ+����)
    //��ʒ��S�� = XY���_(0.0f,0.0f)
    //��ʒ[ = ��X = 1.0f �E = -1.0f ��Y = 1.0f ��Y = -1.0f
    Vertex vertexList[] = {

        //���_�����v���ɎO�p�`���`�����鑤���|���S���̕\�ɂȂ�
        //���ɂȂ��Ă��܂��ƕ`�悳��Ȃ�
        { l, t, 0.5f, 0.0f, 0.0f},      //0�Ԗڂ̒��_���W {x, y, z, u, v}
        { r, b, 0.5f ,uv.x, uv.y},      //1�Ԗڂ̒��_���W
        { l, b, 0.5f ,0.0f ,uv.y},      //2�Ԗڂ̒��_���W

        { l, t, 0.5f, 0.0f, 0.0f},    //3�Ԗڂ̒��_���W
        { r, t, 0.5f, uv.x, 0.0f},    //4�Ԗڂ̒��_���W
        { r, b, 0.5f ,uv.x ,uv.y},    //5�Ԗڂ̒��_���W

    };

    //���_�o�b�t�@���쐬����
    //�����_�o�b�t�@ : VRAM�ɒ��_�f�[�^��u�����߂̋@�\
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = sizeof(vertexList);      //�m�ۂ���o�b�t�@�T�C�Y���w��
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //���_�o�b�t�@�T�C�Y���w��
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResourceData;
    subResourceData.pSysMem = vertexList;            //VRAM�ɑ���f�[�^���w��
    subResourceData.SysMemPitch = 0;
    subResourceData.SysMemSlicePitch = 0;

    //���_�o�b�t�@�쐬���āA�����ϐ�(��R����)�ɕۑ�
    m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, vb);
}

HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture)
{
    //��4����:�ǂݍ��񂾃e�N�X�`����ێ�����ϐ�
    HRESULT hr = DirectX::CreateWICTextureFromFile(m_pDevice, filename, NULL, texture);

    //�ǂݍ��݂Ɏ��s�����ꍇ
    if (FAILED(hr))
        MessageBoxA(NULL, "�e�N�X�`���ǂݍ��݂Ɏ��s", "�G���[", MB_OK | MB_ICONERROR);

    return hr;
}

void D3D_ClearScreen()
{
    //��ʓh��Ԃ��F
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

    //�`���̃L�����o�X�Ǝg�p����[�x�o�b�t�@���w�肷����w�肷��
    //�[�x�o�b�t�@���g��Ȃ��Ƃ��͑�R������NULL�Ɏw�肷��
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
    //�`���L�����o�X��h��Ԃ�
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    //�[�x�o�b�t�@�����Z�b�g����
    m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_pImmediateContext->IASetInputLayout(m_pInputLayout);
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
    m_pImmediateContext->RSSetViewports(1, &m_Viewport);
    m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

    //�s�N�Z���V�F�[�_�[�ɃT���v���[��n��
    m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);

    //�萔�o�b�t�@�ɒ��_�V�F�[�_�[���Z�b�g����
    m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstBuffer);
    //�萔�o�b�t�@�Ƀs�N�Z���V�F�[�_�[���Z�b�g����
    m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstBuffer);
}

void D3D_UpdateScreen()
{
    //�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
    m_pSwapChain->Present(0, 0);
}


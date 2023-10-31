/* ���_�V�F�[�_�[ */

//���_�̃f�[�^��\���\����(�󂯎��p)
struct VS_IN
{
    float4 pos : POSITION0; //�ʒu���W������
    float2 tex : TEX;       //UV���W������
};

//���_�̃f�[�^��\���\����(���M�p)
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

//�O���[�o���ϐ��̐錾
//�萔�o�b�t�@�󂯎��p
cbuffer ConstBuffer : register(b0)
{
    //UV���W�ړ��s��
    matrix matrixTex;
    //���e�s��
    matrix matrixProj;
    //���[���h�ϊ��s��
    matrix matrixWorld;
    //�}�e���A���F
    float4 materialDiffuse;
}

//���_�V�F�[�_�[�̃G���g���|�C���g
VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;

    //���[���h�ϊ��s��𒸓_�Ɋ|����
    input.pos = mul(input.pos,matrixWorld);

    //���s���e�̂��ߍs��𒸓_�Ɋ|����
    output.pos = mul(input.pos,matrixProj);

    //UV���W���ړ�������
    float4 uv;
    uv.xy = input.tex;  //�s��|���Z�̂��߁Afloat4�^�Ɉڂ�
    uv.z = 0.0f;
    uv.w = 1.0f;

    //UV���W�ƈړ��s����|���Z
    uv = mul(uv, matrixTex);

    //�|���Z�̌��ʂ𑗐M�p�ϐ��ɃZ�b�g����
    output.tex = uv.xy;

    return output;
}
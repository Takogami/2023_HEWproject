#pragma once
#include "CGameObject.h"

//�^�C�g������V�[���ړ��ł��鐔
#define SCENE_COUNT 3

//�^�C�g���̃J�[�\���̈ʒu�̗񋓌^
enum class CCursor_Point
{
    STAGE,
    OPTION,
    EXIT,
};

class CCursor :
    public CGameObject
{
private:
    /* �����o�ϐ� */

    int scene_count;


public:
    /* �����o�ϐ� */

    // �����x�N�g��
    DirectX::XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };

    /* ���\�b�h */

    CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex);
    void Update() override;
    void Draw() override;
    CCursor_Point GetCursorPoint()const;
    ~CCursor() override;
};

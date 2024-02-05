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

//�ʖ��Ŋ֘A�t����
enum class CCursor_PointResult
{
    RETRY = (int)CCursor_Point::STAGE,
    SELECT = (int)CCursor_Point::OPTION,
    TITLE = (int)CCursor_Point::EXIT,
};

class CCursor :
    public CGameObject
{
private:
    /* �����o�ϐ� */

    int scene_count = 0;

    // �����ʒu
    FLOAT_XY ini_position = { 0.0f, 0.0f };
    // �J�[�\���̓�������
    float moveDistance = 0.3f;

public:
    /* ���\�b�h */

    CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex);
    void Update() override;
    void Draw() override;

    // �J�[�\���̏�����
    // ����1 : �����ʒu ����2 : ��������
    void Init(FLOAT_XY ini_pos, float move = 0.3f);

    //�^�C�g����ʂł̃|�C���g�ʒu���擾
    CCursor_Point GetCursorPoint()const;

    ~CCursor() override;
};

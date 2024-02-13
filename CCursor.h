#pragma once
#include "CGameObject.h"

class CEase;

//���U���g�V�[���̃J�[�\��
enum class CCursor_PointResult
{
    RETRY,
    SELECT,
    TITLE,
    INACTIVE,
};

//�ʖ��Ŋ֘A�t����
enum class CCursor_Point
{
    STAGE = (int)CCursor_PointResult::RETRY,
    EXIT = (int)CCursor_PointResult::SELECT,
    INACTIVE,
};

//�ʖ��Ŋ֘A�t����
enum class CCursor_PointClear
{
    SELECT = (int)CCursor_PointResult::RETRY,
    TITLE = (int)CCursor_PointResult::SELECT,
    INACTIVE,
};

class CCursor :
    public CGameObject
{
private:
    /* �����o�ϐ� */

    int scene_count = 0;

    // �J�ڂł���V�[����
    int sceneNum = 3;

    // �����ʒu
    FLOAT_XY ini_position = { 0.0f, 0.0f };
    // �J�[�\���̓�������
    float moveDistance = 0.3f;
    // �J�[�\���̃C�[�W���O
    CEase* curEase;
    bool curReturn = false;

public:
    /* ���\�b�h */

    CCursor(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv ={ 1.0f ,1.0f }, OBJECT_TYPE type = OBJECT_TYPE::NORMAL);
    void CursorInput();
    void Update() override;
    void Draw() override;

    // �J�[�\���̏�����
    // ����1 : �����ʒu ����2 : �J�ڂł���V�[���� ����3 : ��������
    void Init(FLOAT_XY ini_pos, int scene = 3, float move = 0.3f);

    //�^�C�g����ʂł̃|�C���g�ʒu���擾
    CCursor_Point GetCursorPoint()const;

    ~CCursor() override;
};

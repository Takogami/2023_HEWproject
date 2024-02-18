#undef UNICODE  // Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��

#include <Windows.h>
#include <Windowsx.h>
#include "direct3d.h"
#include "CGame.h"
#include "CInput.h"

// �}�N����`
#define CLASS_NAME    "DX21Smpl"// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME   "���݂؂�����"// �E�B���h�E�̖��O

// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�O���[�o���ϐ��̐錾
CGame* gGame;
CInput* gInput = new CInput;

//�G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	/* �E�C���h�E�̃p�����[�^�i�X�^�C���Ȃǁj�����߂āAWindows�ɓo�^ */

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;								//�A�C�R���̕ύX
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		//�J�[�\���ύX
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;							//�E�C���h�E�̃��j���[�ݒ�
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	/* �E�C���h�E�����֐����Ăяo�� */

	// ��ʃT�C�Y���擾
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd; // �E�C���h�E�n���h�� = �E�C���h�EID
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_POPUP,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W
		screenX,// �E�B���h�E�̕�
		screenY,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	/* �E�C���h�E��\������֐����Ăяo�� */

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	//�Q�[�����[�v�ɓ���O��DirectX�̏�����������
	D3D_Create(hWnd);

	//�Q�[���̏�����
	gGame = new CGame();

	/* �A�v�����I���Ȃ��悤�ɉi�v���[�v�����
	�����[�v�̒��Ń��[�U�[�̑����҂��\���� */
	MSG msg;

	char str[100];

	//fps�\���p
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();	//�J�n���Ԃ�ۑ�
	long long nowTick = oldTick;			//���ݎ��Ԃ��擾

	//fps�Œ�p�ϐ�
	LARGE_INTEGER liWork;	//�֐�����l���󂯎��p
	long long frequency;	//�v�����x

	//�v�����x���擾
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;	//�P�b������̉𑜓x������
	//1�t���[��������̃J�E���g�l���v�Z
	long long numCount_1flame = frequency / 60;	//60fps�Ōv�Z
	//���ݎ���(�P�ʁF�J�E���g)���擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	//���b�Z�[�W���[�v(�Q�[�����[�v)
	while (true) {
		//���[�U�[����(�C�x���g)���N�����������ׂ�
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage)
		{
			//�C�x���g���N�������̂ŃR�[���o�b�N���Ăяo��
			DispatchMessage(&msg);

			//�A�v�����I�������郁�b�Z�[�W��������i�v���[�v���甲����(break�Ŕ�����)
			if (msg.message == WM_QUIT) {
				break;
			
			}
		}
		//�������b�Z�[�W���Ȃ��Ƃ�
		else {

			//1/60�b�o�߂������H
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart;	//���ݎ��Ԃ��擾(�P�ʁF�J�E���g)

			if (nowCount >= oldCount + numCount_1flame) {
				//�Q�[���̏���
				gGame->Update();
				gInput->Update();
				fpsCounter++;	//�Q�[�����[�v���s�֐����{�P
				oldCount = nowCount;
			}

			nowTick = GetTickCount64();

			//1�b�o�߂������H
			//+1000 �c �~���b�P�ʂł��邽��
			if (nowTick >= oldTick + 1000) {

				//fps��\������
				wsprintfA(str, "���݂؂�����    FPS : %d", fpsCounter);
				SetWindowTextA(hWnd, str);
				//�J�E���^�[�����Z�b�g
				fpsCounter = 0;
				oldTick = nowTick;
			}

		}
	}	//end gameloop

	delete gGame;
	delete gInput;

	//DirectX�̉������
	D3D_Release();

	// ���[�v�𔲂�����A�v���̏I������������
	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �gWM_QUIT�h���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		DestroyWindow(hWnd);  // �gWM_DESTROY�h���b�Z�[�W�𑗂�
		break;

	case WM_KEYDOWN:
		gInput->SetKeyDownState(wParam);
		break;

	case WM_KEYUP:
		gInput->SetKeyUpState(wParam);
		break;

	default:
		// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
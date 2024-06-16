#pragma once
#include "DxLib.h"
#include <list>
#include <ctype.h> 

struct MOJI_DATA
{
	char moji[3];
};

std::list<MOJI_DATA>	g_fonts;		// �����f�[�^
int g_InputHandle;						// �C���v�b�g�n���h��

void dataUpdate(void);					// �f�[�^���X�V
void drawData(void);					// �f�[�^�\��

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);
	SetMainWindowText("�����񕪊��Ă���");
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	g_InputHandle = MakeKeyInput(30, FALSE, FALSE, FALSE);

	// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	SetActiveKeyInput(g_InputHandle);

	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���[�v
	while (!ProcessMessage())
	{
		bool isUpdateData = false;

		// ���͂��I�����Ă���ꍇ�͏I��
		if (CheckKeyInput(g_InputHandle) != 0) break;

		// ��ʂ̃N���A
		ClearDrawScreen();

		// ���̓��[�h��`��
		DrawKeyInputModeString(640, 480);

		// ���͓r���̕������`��
		DrawKeyInputString(0, 0, g_InputHandle);

		dataUpdate();

		drawData();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	// �p�ς݂̃C���v�b�g�n���h�����폜����
	DeleteKeyInput(g_InputHandle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}


void dataUpdate()
{
	char String[256];

	// ���͂��ꂽ��������擾
	GetKeyInputString(String, g_InputHandle);

	g_fonts.clear();

	// �ׂ�����肱�ނ̂��ʓ|�������ׂɎד������B
	for (int j = 0; j < strlen(String); j++)
	{
		MOJI_DATA add_data;

		if (isalnum((int)String[j]) != 0)
		{
			// ���p
			//sprintf(add_data.moji, "%c", String[j]);
		}
		else
		{
			// �S�p�B�ד������B�悢�q�͐^��������ʖځB
			//sprintf(add_data.moji, "%c%c", String[j], String[j + 1]);
			j++;
		}
		g_fonts.push_back(add_data);
	}
}

void drawData()
{
	int ypos = 14;
	int count = 0;
	::std::list<MOJI_DATA>::iterator ite;
	for (ite = g_fonts.begin(); ite != g_fonts.end(); ite++)
	{
		DrawFormatString(0, ypos, GetColor(255, 255, 255), "%02d:%s", count, ite->moji);
		ypos += 14;
		count++;
	}
}